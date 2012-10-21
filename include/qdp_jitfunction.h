#ifndef QDP_JITFUNC_H
#define QDP_JITFUNC_H

#include "qmp.h"

namespace QDP {


template<class T, class T1, class Op, class RHS>
CUfunction
function_build(OLattice<T>& dest, const Op& op, const QDPExpr<RHS,OLattice<T1> >& rhs)
{
  std::cout << __PRETTY_FUNCTION__ << ": entering\n";

  CUfunction func;

  Jit function("ptxtest.ptx","func");

  std::cout << "function = " << (void*)&function <<"\n";

  ParamLeaf param_leaf(function,function.getRegIdx());

  // Destination
  typedef typename LeafFunctor<OLattice<T>, ParamLeaf>::Type_t  FuncRet_t;
  FuncRet_t dest_jit(forEach(dest, param_leaf, TreeCombine()));

  // Now the arguments for the rhs
  typedef typename ForEach<QDPExpr<RHS,OLattice<T1> >, ParamLeaf, TreeCombine>::Type_t View_t;
  View_t rhs_view(forEach(rhs, param_leaf, TreeCombine()));

  printme<View_t>();

  op(dest_jit.elem(0), forEach(rhs_view, ViewLeaf(0), OpCombine()));

  if (Layout::primaryNode())
    function.write();
      
  QMP_barrier();

  CUresult ret;
  CUmodule cuModule;
  ret = cuModuleLoad(&cuModule, "ptxtest.ptx");
  if (ret) { std::cout << "Error loading CUDA module\n"; exit(1); }

  ret = cuModuleGetFunction(&func, cuModule, "func");
  if (ret) { std::cout << "Error getting function\n"; exit(1); }

  std::cout << __PRETTY_FUNCTION__ << ": exiting\n";

  return func;
}



template<class T, class T1, class RHS>
CUfunction
function_gather_build( void* send_buf , const Map& map , const QDPExpr<RHS,OLattice<T1> >& rhs )
{
  std::cout << __PRETTY_FUNCTION__ << ": entering\n";

  void * soffsetDev = QDPCache::Instance().getDevicePtr( map.getSoffsetsId() );
  QDP_info("soffsetDev = %p",soffsetDev);

  ShiftPhase1 phase1;
  int maps_involved = forEach(rhs, phase1 , BitOrCombine());

  QDP_info("maps_involved=%d",maps_involved);

  if (maps_involved > 0) {
    int innerId = MasterMap::Instance().getIdInner(maps_involved);
    int innerCount = MasterMap::Instance().getCountInner(maps_involved);
    int faceId = MasterMap::Instance().getIdFace(maps_involved);
    int faceCount = MasterMap::Instance().getCountFace(maps_involved);
  }

  CUfunction func;

  Jit function("ptxgather.ptx","func");

  std::cout << "function = " << (void*)&function <<"\n";

  ParamLeaf param_leaf_0( function , function.getRegIdx() );
  ParamLeaf param_leaf_soffset( function , param_leaf_0.getParamIndexField() );

  // Destination
  typedef typename JITContainerType< OLattice<T> >::Type_t DestView_t;
  DestView_t dest_jit( function , param_leaf_0.getParamLattice( WordSize<T>::Size ) );

  // typedef typename LeafFunctor<OLattice<T>, ParamLeaf>::Type_t  FuncRet_t;
  // FuncRet_t dest_jit(forEach(dest, param_leaf, TreeCombine()));

  // Now the arguments for the rhs
  typedef typename ForEach<QDPExpr<RHS,OLattice<T1> >, ParamLeaf, TreeCombine>::Type_t View_t;
  View_t rhs_view( forEach( rhs , param_leaf_soffset , TreeCombine() ) );

  printme<View_t>();

  OpAssign()(dest_jit.elem(0), forEach(rhs_view, ViewLeaf(0), OpCombine()));

#if 1
  if (Layout::primaryNode())
    function.write();
#endif

  QMP_barrier();

  CUresult ret;
  CUmodule cuModule;
  ret = cuModuleLoad(&cuModule, "ptxgather.ptx");
  if (ret) { std::cout << "Error loading CUDA module\n"; exit(1); }

  ret = cuModuleGetFunction(&func, cuModule, "func");
  if (ret) { std::cout << "Error getting function\n"; exit(1); }

  std::cout << __PRETTY_FUNCTION__ << ": exiting\n";

  return func;
}


template<class T1, class RHS>
void
function_gather_exec( CUfunction function, void* send_buf , const Map& map , const QDPExpr<RHS,OLattice<T1> >& rhs )
{
#if 1
  std::cout << __PRETTY_FUNCTION__ << ": entering\n";

  AddressLeaf addr_leaf;

  int junk_rhs = forEach(rhs, addr_leaf, NullCombine());

  QDPCache::Instance().printLockSets();

  // lo <= idx < hi
  int lo = 0;
  int hi = map.soffset().size();
  QDP_info("gather sites into send_buf lo=%d hi=%d",lo,hi);

  int goffsetsId = map.getGoffsetsId();
  void * goffsetsDev = QDPCache::Instance().getDevicePtr( goffsetsId );

  QDPCache::Instance().printLockSets();

  std::vector<void*> addr;

  addr.push_back( &lo );
  std::cout << "addr lo =" << addr[0] << "\n";

  addr.push_back( &hi );
  std::cout << "addr hi =" << addr[1] << "\n";

  addr.push_back( &goffsetsDev );
  std::cout << "addr goffsetsDev =" << addr[2] << "\n";

  addr.push_back( &send_buf );
  std::cout << "addr send_buf =" << addr[3] << "\n";

  for(int i=0; i < addr_leaf.addr.size(); ++i) {
    addr.push_back( &addr_leaf.addr[i] );
    std::cout << "addr rhs =" << addr[addr.size()-1] << " " << addr_leaf.addr[i] << "\n";
  }



  static int threadsPerBlock = 0;

  if (!threadsPerBlock) {
    // Auto tuning

    double best_time;
    int best_cfg=-1;
    bool first=true;
    for ( int cfg = 1 ; cfg <= DeviceParams::Instance().getMaxBlockX(); cfg *= 2 ) {
      kernel_geom_t now = getGeom( hi-lo , cfg );

      StopWatch w;
      CUresult result = CUDA_SUCCESS;

      for (int i=0 ; i < 10 && result == CUDA_SUCCESS; i++) {
	if (i==1) w.start();
	result = cuLaunchKernel(function,   now.Nblock_x,now.Nblock_y,1,    cfg,1,1,    0, 0, &addr[0] , 0);
	CudaDeviceSynchronize();
      }

      if (result == CUDA_SUCCESS) {
	w.stop();
	double time = w.getTimeInMicroseconds();
	QDP_info_primary("launched threads per block = %d grid = (%d,%d) (time=%f micro secs)",cfg,now.Nblock_x,now.Nblock_y,time);
	if (first) {
	  best_time = time;
	  best_cfg = cfg;
	  first = false;
	} else {
	  if (time < best_time) {
	    best_time = time;
	    best_cfg = cfg;
	  }
	}
      } else {
	QDP_info_primary("tried threads per block = %d, failed, code = %d ",cfg,result);
      }
    }

    if (best_cfg < 0)
      QDP_error_exit("Auto-tuning failed!");

    QDP_info_primary("Threads per block favored = %d  (time=%f micro secs)",best_cfg,best_time);
    threadsPerBlock = best_cfg;
  } else {
    //QDP_info_primary("Previous auto-tuning result = %d",threadsPerBlock);
  }

  kernel_geom_t now = getGeom( hi-lo , threadsPerBlock );
  CUresult result = CUDA_SUCCESS;
  result = cuLaunchKernel(function,   now.Nblock_x,now.Nblock_y,1,    threadsPerBlock,1,1,    0, 0, &addr[0] , 0);

  if (DeviceParams::Instance().getSyncDevice()) {  
    QDP_info_primary("Pulling the brakes: device sync after kernel launch!");
    CudaDeviceSynchronize();
  }
#endif
}




template<class T, class T1, class Op, class RHS>
void 
function_exec(CUfunction function, OLattice<T>& dest, const Op& op, const QDPExpr<RHS,OLattice<T1> >& rhs)
{
#if 1
  //std::cout << __PRETTY_FUNCTION__ << ": entering\n";


  ShiftPhase1 phase1;
  int maps_involved = forEach(rhs, phase1 , BitOrCombine());

  QDP_info("maps_involved=%d",maps_involved);

  if (maps_involved > 0) {

    int innerId = MasterMap::Instance().getIdInner(maps_involved);
    int innerCount = MasterMap::Instance().getCountInner(maps_involved);
    int faceId = MasterMap::Instance().getIdFace(maps_involved);
    int faceCount = MasterMap::Instance().getCountFace(maps_involved);



  } else {

    AddressLeaf addr_leaf;

    int junk_dest = forEach(dest, addr_leaf, NullCombine());
    int junk_rhs = forEach(rhs, addr_leaf, NullCombine());

    // lo <= idx < hi
    int lo = 0;
    int hi = Layout::sitesOnNode();
    std::vector<void*> addr;
    addr.push_back( &lo );
    std::cout << "addr=" << addr[0] << "\n";
    addr.push_back( &hi );
    std::cout << "addr=" << addr[1] << "\n";
    int addr_dest=addr.size();
    for(int i=0; i < addr_leaf.addr.size(); ++i) {
      addr.push_back( &addr_leaf.addr[i] );
      std::cout << "addr=" << addr_leaf.addr[i] << "\n";
    }

    static int threadsPerBlock = 0;

    if (!threadsPerBlock) {
      // Auto tuning

      // Fist get a data field of the same size as "dest" where we can play on
      // (in case the final operator is an OpAddAssign, etc.)
      int tmpId = QDPCache::Instance().registrate( QDPCache::Instance().getSize( dest.getId() ) , 1 , NULL );
      void * devPtr = QDPCache::Instance().getDevicePtr( tmpId );
      //QDPCache::Instance().printLockSets();
      addr[addr_dest] = &devPtr;

      double best_time;
      int best_cfg=-1;
      bool first=true;
      for ( int cfg = 1 ; cfg <= DeviceParams::Instance().getMaxBlockX(); cfg *= 2 ) {
	kernel_geom_t now = getGeom( hi-lo , cfg );

	StopWatch w;
	CUresult result = CUDA_SUCCESS;

	for (int i=0 ; i < 10 && result == CUDA_SUCCESS; i++) {
	  if (i==1) w.start();
	  result = cuLaunchKernel(function,   now.Nblock_x,now.Nblock_y,1,    cfg,1,1,    0, 0, &addr[0] , 0);
	  CudaDeviceSynchronize();
	}

	if (result == CUDA_SUCCESS) {
	  w.stop();
	  double time = w.getTimeInMicroseconds();
	  QDP_info_primary("launched threads per block = %d grid = (%d,%d) (time=%f micro secs)",cfg,now.Nblock_x,now.Nblock_y,time);
	  if (first) {
	    best_time = time;
	    best_cfg = cfg;
	    first = false;
	  } else {
	    if (time < best_time) {
	      best_time = time;
	      best_cfg = cfg;
	    }
	  }
	} else {
	  QDP_info_primary("tried threads per block = %d, failed, code = %d ",cfg,result);
	}
      }

      if (best_cfg < 0)
	QDP_error_exit("Auto-tuning failed!");

      QDP_info_primary("Threads per block favored = %d  (time=%f micro secs)",best_cfg,best_time);
      threadsPerBlock = best_cfg;

      // Restore original "dest" device address
      addr[addr_dest] = &addr_leaf.addr[0];
      QDPCache::Instance().signoff( tmpId );
      //QDPCache::Instance().printLockSets();

    } else {
      //QDP_info_primary("Previous auto-tuning result = %d",threadsPerBlock);
    }

    kernel_geom_t now = getGeom( hi-lo , threadsPerBlock );
    CUresult result = CUDA_SUCCESS;
    result = cuLaunchKernel(function,   now.Nblock_x,now.Nblock_y,1,    threadsPerBlock,1,1,    0, 0, &addr[0] , 0);

    if (DeviceParams::Instance().getSyncDevice()) {  
      QDP_info_primary("Pulling the brakes: device sync after kernel launch!");
      CudaDeviceSynchronize();
    }
  }
#endif
}


}

#endif
