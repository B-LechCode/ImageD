/************************************
 *   added:     ??.03.2020          *
 *   author:    David Eilenstein    *
 *   contact:   D.Eilenstein@gsi.de *
 *   project:   ImageD              *
 *   facility:  GSI Darmstadt, Ger  *
 ************************************/

#ifndef D_MAKRO_MEGAFOCI_H
#define D_MAKRO_MEGAFOCI_H

//own
#include <d_enum.h>
#include <d_error_handler.h>
#include <d_visdat_proc.h>
#include <d_plot.h>
#include <d_stat.h>
#include <d_viewer.h>
#include <d_storage.h>
#include <d_table.h>
#include <d_popup_listedit.h>
#include <d_videowriter.h>

//Qt
#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QDateTime>
#include <QComboBox>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QInputDialog>
#include <qplaintextedit.h>
#include <QColorDialog>
#include <QLabel>

//Qt::Charts
#include <QChartView>
#include <QChart>

//general
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

//openCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//namespaces
using namespace std;
using namespace cv;

namespace Ui {
class D_MAKRO_MegaFoci;
}

class D_MAKRO_MegaFoci : public QMainWindow
{
    Q_OBJECT

public:
    explicit D_MAKRO_MegaFoci(D_Storage *pStorage, QWidget *parent = nullptr);
    ~D_MAKRO_MegaFoci();

    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void set_ClosingPossible(bool closeable)     {ClosingPossible = closeable;}

private slots:
    void Update_Ui();
    void Update_Views();
    void Update_Images();
    void Update_Images_Proc();
    void Update_Images_OverviewSmall();
    void Update_Images_OverviewBig();

    void Update_ImageProcessing_CurrentImage();
    void Update_ImageProcessing_StepFrom(size_t step_start);
    void Update_ImageProcessing_StepSingle(size_t step);

    void Populate_CB_AtStart();
    void Populate_CB_Single(QComboBox *CB, QStringList QSL, int init_index = 0);

    bool Load_Dataset();
    void Overview_Init();
    void Overview_Update();

    bool LoadShow_Image_UiSelected();    
    int  Load_Image_full_ZP_Stitched_UiSelected(D_VisDat_Obj *pVD_Target);
    bool Load_Image_UiSelected(Mat *pMA_Target);
    bool Load_Image(Mat *pMA_Target, size_t x, size_t y, size_t z, size_t t, size_t p);
    int  Load_Image_full_ZP(D_VisDat_Obj *pVD_Target, size_t x, size_t y, size_t t);
    int  Load_Image_full_ZP_Stitched(D_VisDat_Obj *pVD_Target, size_t x, size_t y, size_t t);

    void set_dataset_dim_x(int x) {if(!state_dataset_dim_set) {dataset_dim_mosaic_x = x; dataset_dim_mosaic_xy = dataset_dim_mosaic_x * dataset_dim_mosaic_y;}}
    void set_dataset_dim_y(int y) {if(!state_dataset_dim_set) {dataset_dim_mosaic_y = y; dataset_dim_mosaic_xy = dataset_dim_mosaic_x * dataset_dim_mosaic_y;}}
    void set_dataset_dim_t(int t) {if(!state_dataset_dim_set) {dataset_dim_t = t; dataset_dim_tzp = dataset_dim_t * dataset_dim_z * dataset_dim_p;}}
    void set_dataset_dim_z(int z) {if(!state_dataset_dim_set) {dataset_dim_z = z; dataset_dim_tzp = dataset_dim_t * dataset_dim_z * dataset_dim_p;}}

    void StatusSet(QString NewStatus);

    void on_comboBox_VisTrafo_CropMode_currentIndexChanged(int index);
    void on_comboBox_VisTrafo_TransformationMode_currentIndexChanged(int index);
    void on_comboBox_VisTrafo_AnchorMode_currentIndexChanged(int index);
    void on_comboBox_VisTrafo_RangeMode_currentIndexChanged(int index);

    void on_comboBox_ImgProc_StepShow_currentIndexChanged(int index);

    void on_spinBox_Viewport_P_valueChanged(int arg1);

    void on_doubleSpinBox_ImgProc_Stitch_Border_valueChanged(double arg1);
    void on_doubleSpinBox_ImgProc_Stitch_Overlap_valueChanged(double arg1);
    void on_comboBox_ImgProc_ProjectZ_Stat_currentIndexChanged(int index);
    void on_spinBox_ImgProc_GFP_BlurMedianSize_valueChanged(int arg1);
    void on_doubleSpinBox_ImgProc_GFP_ThresEdges_valueChanged(double arg1);
    void on_doubleSpinBox_ImgProc_GFP_AreaMin_valueChanged(double arg1);
    void on_doubleSpinBox_ImgProc_GFP_AreaMax_valueChanged(double arg1);
    void on_doubleSpinBox_ImgProc_GFP_DistThres_valueChanged(double arg1);
    void on_checkBox_ImgProc_NucWatershed_NonSeed_clicked();
    void on_checkBox_ImgProc_NucWatershed_ExBordered_clicked();

    void on_tabWidget_Control_currentChanged(int index);

private:
    Ui::D_MAKRO_MegaFoci *ui;
    bool ClosingPossible = false;

    //error handling
    D_Error_Handler ER;
    void ERR(int err, QString func = "not specified", QString detail = "not specified");

    //Storage
    D_Storage                           *pStore;

    //states
    bool                                state_dataset_dim_set = false;
    bool                                state_dataset_img_list_loaded = false;
    bool                                state_overview_init = false;

    //data files
    QFileInfoList                       FIL_Images;
    QStringList                         QSL_Images_Paths;
    QStringList                         QSL_Images_Names;
    QStringList                         QSL_Images_Suffix;

    //dataset dimension
    size_t                              dataset_dim_mosaic_x = 15;
    size_t                              dataset_dim_mosaic_y = 15;
    size_t                              dataset_dim_mosaic_xy = 15 * 15;
    size_t                              dataset_dim_z = 6;
    size_t                              dataset_dim_t = 42;
    const size_t                        dataset_dim_p = 2;
    size_t                              dataset_dim_tzp = 42 * 6 * 2;
    size_t                              dataset_dim_img_x = 1004;
    size_t                              dataset_dim_img_y = 1002;
    int                                 dataset_type_mat = CV_16UC1;
    int                                 dataset_depth_mat = CV_16U;
    size_t                              get_index_of_image(size_t x, size_t y);
    size_t                              get_index_of_page(size_t z, size_t t, size_t p);

    //Main Viewer
    D_VisDat_Obj                        VD_Show;
    Mat                                 MA_Show;
    D_Viewer                            Viewer_Main;

    //img proc
    vector<D_VisDat_Obj>                vVD_ImgProcSteps;

    //overview
    double                              overview_scale = 0.10;
    size_t                              overview_SubImgSizeX = overview_scale * dataset_dim_img_x;
    size_t                              overview_SubImgSizeY = overview_scale * dataset_dim_img_y;
    D_VisDat_Obj                        VD_Overview_Save;
    Mat                                 MA_OverviewSmall_Show;
    Mat                                 MA_OverviewBig_Show;
    D_Viewer                            Viewer_OverviewSmall;
    D_Viewer                            Viewer_OverviewBig;

    //Status
    const int                           status_EntryNumber = 250;
    QStringList                         QSL_Status;

    //Statusbar
    QLabel                              *L_SB_ValueAtCursor;
    QLabel                              *L_SB_InfoVD;

    //Pages
    enum PAGES {
        PAGE_GFP,
        PAGE_RFP,
        PAGES_NUMBER_OF
    };
    const QStringList QSL_Pages = {
        "GFP",
        "RFP"
    };

    //Img Proc Step
    enum STEPS {
        STEP_LOAD_MAIN,
        STEP_LOAD_RIGHT,
        STEP_LOAD_BOTTOM,
        STEP_LOAD_BOTTOM_RIGHT,
        STEP_STITCH,
        STEP_PROJECT_Z,
        STEP_P0_PICK,
        STEP_P1_PICK,
        STEP_PAGES_AS_COLOR,
        STEP_P0_BLUR_MEDIAN,
        STEP_P0_EDGE_CV,
        STEP_P0_BINARY_THRES,
        STEP_P0_BINARY_FILL_HOLES,
        STEP_P0_BINARY_AREA_SELECT,
        STEP_P0_DISTANCE,
        STEP_P0_SEEDS,
        STEP_P0_WATERSHED,
        STEP_NUMBER_OF
    };
    const QStringList QSL_Steps = {
        "00 Load main image",
        "01 Load border image R",
        "02 Load border image B",
        "03 Load border image BR",
        "04 Stitch borders to main image",
        "05 Z-Projection",
        "06 GFP pick signal",
        "07 RFP pick Signal",
        "08 Color GFP blue RFP green",
        "09 GFP circular median blur",
        "10 GFP circular CV edges",
        "11 GFP binarize edge image",
        "12 GFP fill holes in edge image",
        "13 GFP select nuclei sized",
        "14 GFP distance transformation",
        "15 GFP nuclei segmentation seeds",
        "16 Nuclei watershed segmentation"
    };

    //Tabs
    enum TABS_CONTROL {
        TAB_CONTROL_IMG_PROC,
        TAB_CONTROL_OVERVIEW_BIG,
        TAB_CONTROL_NUMBER_OF
    };

    //View
    enum VIEW_PAGE {
        VIEW_PAGE_IMG_PROC,
        VIEW_PAGE_OVERVIEW_BIG,
        VIEW_PAGE_PLOT
    };

};

#endif // D_MAKRO_MEGAFOCI_H
