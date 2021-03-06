#pragma once

#include <ndt_generic/gnuplot-iostream.h>
#include <ndt_generic/io.h>
#include <ndt_generic/motion_model_3d.h>
#include <ndt_map/pointcloud_utils.h>
#include <ndt_registration/icp_matcher_p2p.h>
#include <ndt_registration/ndt_matcher_d2d_sc.h>
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
#include <boost/tuple/tuple.hpp>

class RegistrationScore {
  public:
    Eigen::Affine3d offset;
    double score_d2d;
    double score_d2d_sc;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

// To evaluate the objective function with and without soft constraints, to interface the files
// generated by the offline fuser
class RegistrationScoreEval {
  public:
    RegistrationScoreEval( const std::string& gt_file, const std::string& odom_file,
                           const std::string& base_name_pcd, const Eigen::Affine3d& sensor_pose,
                           const perception_oru::MotionModel3d::Params& motion_params );

    bool setGlobalMap( const std::string& file_name, const Eigen::Affine3d& T );
    bool setGlobalGraphMap( const std::string& file_name, int node_idx );

    std::vector< Eigen::Affine3d > generateOffsetSet();

    std::vector< Eigen::Affine3d > generateOffset2DSet( int dimidx1, int dimidx2 );

    int nbPoses() const;

    void computeScoreSets( int idx1, int idx2, int dimidx1, int dimidx2 );
    void computeScoreSetsGlobalMap( int idx2, int dimidx1, int dimidx2 );

    void save( const std::string& filename, int grididx ) const;

    // Save in a 2d grid, to be able to plot a 2d grid with different colors (gnuplot pm3d)
    void save2D( const std::string& filename, int dimidx1, int dimidx2 ) const;

    void savePCD( const std::string& filename ) const;

    // Saves in the same frame as with the offset is used (the odometry frame)
    void savePoseEstInOdomFrame( const std::string& filename ) const;
    void saveTsToEvalFiles( const std::string& filename ) const;
    void saveComputationTime( const std::string& filename ) const;
    std::vector< std::vector< boost::tuple< double, double, double > > >
    getScoreSegments( int dimidx1, int dimidx2, bool d2d_sc_score ) const;
    std::vector< std::vector< boost::tuple< double, double, double > > >
    getRelPoseGT( int dimidx1, int dimidx2 ) const;
    std::vector< boost::tuple< double, double, double > > getRelPoseD2D( int dimidx1,
                                                                         int dimidx2 ) const;
    std::vector< boost::tuple< double, double, double > > getRelPoseD2D_SC( int dimidx1,
                                                                            int dimidx2 ) const;
    std::vector< boost::tuple< double, double, double > > getRelPoseICP( int dimidx1,
                                                                         int dimidx2 ) const;
    std::vector< boost::tuple< double, double, double > > getRelPoseFilter( int dimidx1,
                                                                            int dimidx2 ) const;
    std::vector< boost::tuple< double, double, double > > getRelPoseICPFilter( int dimidx1,
                                                                               int dimidx2 ) const;
    std::vector< boost::tuple< double, double, double > > getRelPoseOdom( int dimidx1,
                                                                          int dimidx2 ) const;

    // Parameters
    double resolution;   // resolution for the ndt map

    int offset_size;
    double incr_dist;
    double incr_ang;

    bool use_d2d_in_grid;
    bool use_d2d_sc_in_grid;

  private:
    std::vector< Eigen::Affine3d > Todom;
    std::vector< Eigen::Affine3d > Tgt;

    std::string base_name_pcd_;
    Eigen::Affine3d sensor_pose_;

    perception_oru::MotionModel3d motion_model;

    std::vector< RegistrationScore > results;
    double alpha_;

    Eigen::Affine3d T_rel_;

    Eigen::Affine3d T_d2d_;
    Eigen::Affine3d T_d2d_sc_;
    Eigen::Affine3d T_icp_;
    Eigen::Affine3d T_filter_;
    Eigen::Affine3d T_icp_filter_;
    Eigen::Affine3d T_rel_gt_;
    Eigen::Affine3d T_rel_odom_;

    Eigen::Affine3d T_glb_d2d_;
    Eigen::Affine3d T_glb_d2d_sc_;
    Eigen::Affine3d T_glb_icp_;
    Eigen::Affine3d T_glb_filter_;
    Eigen::Affine3d T_glb_icp_filter_;
    Eigen::Affine3d T_glb_gt_;
    Eigen::Affine3d T_glb_odom_;

    std::vector< Eigen::Affine3d > Ts_glb_d2d_;
    std::vector< Eigen::Affine3d > Ts_glb_d2d_sc_;
    std::vector< Eigen::Affine3d > Ts_glb_icp_;
    std::vector< Eigen::Affine3d > Ts_glb_filter_;
    std::vector< Eigen::Affine3d > Ts_glb_icp_filter_;
    std::vector< Eigen::Affine3d > Ts_glb_gt_;
    std::vector< Eigen::Affine3d > Ts_glb_odom_;

    std::vector< double > time_d2d_;
    std::vector< double > time_d2d_sc_;

    pcl::PointCloud< pcl::PointXYZ > pc_odom_, pc_d2d_, pc_d2d_sc_, pc_icp_, pc_gt_, pc1_,
        pc_icp_final_;
    perception_oru::NDTMap global_ndtmap_;
    Eigen::Affine3d global_ndtmap_T_;
};
