// *****************************************************************************
//  handling right click event, calls service which will display a
//  number of services that are available on that specific location
//
// *****************************************************************************


#ifndef MAPVIZ_PLUGINS_right_click_services_H
#define MAPVIZ_PLUGINS_right_click_services_H

// Include mapviz_plugin.h first to ensure GL deps are included in the right order
#include <mapviz/mapviz_plugin.h>

#include <QGLWidget>
#include <QTimer>
#include <mapviz/map_canvas.h>
#include <QMouseEvent>
#include <mapviz_plugins/canvas_click_filter.h>

#include <ros/ros.h>

// QT autogenerated files
#include "ui_right_click_services_config.h"
#include "ui_topic_select.h"

/**
 * This is a pretty straightforward plugin.  It watches for user clicks on the
 * canvas, then converts the coordinates into a specified frame and publishes
 * them as PointStamped messages on a specified topic.
 */
namespace mapviz_plugins
{
  class RightClickServicesPlugin : public mapviz::MapvizPlugin
  {
    Q_OBJECT;
  public:

    RightClickServicesPlugin();
    virtual ~RightClickServicesPlugin();

    bool Initialize(QGLWidget* canvas);
    void Shutdown() {}

    virtual void SetNode(const ros::NodeHandle& node);
    virtual void PrintError(const std::string& message);
    virtual void PrintInfo(const std::string& message);
    virtual void PrintWarning(const std::string& message);

    void Draw(double x, double y, double scale);

    void Transform() {}

    void LoadConfig(const YAML::Node& node, const std::string& path);
    void SaveConfig(YAML::Emitter& emitter, const std::string& path);

    QWidget* GetConfigWidget(QWidget* parent);


    void serviceCall(std::string service);


  protected Q_SLOTS:

    void pointClicked(const QPointF& point, const Qt::MouseButton& button);
    void topicChanged(const QString& topic);
    void updateFrames();


  private:
    void showContextMenu(const QPoint& pos, boost::shared_ptr<geometry_msgs::PointStamped> stamped);
    Ui::right_click_services_config ui_;
    QWidget* config_widget_;

    CanvasClickFilter click_filter_;
    mapviz::MapCanvas* canvas_;

    QTimer frame_timer_;
    ros::Publisher point_publisher_;
  };
}

#endif //MAPVIZ_PLUGINS_right_click_services_H