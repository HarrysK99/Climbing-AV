#define DEBUG
#define RELEASE
// #undef RELEASE
#undef DEBUG

#ifdef RELEASE
#include <ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>

// ROS 노드 및 토픽 정의
ros::NodeHandle nh;
std_msgs::Float32 float_msg;
std_msgs::Bool bool_msg;
std_msgs::Int8 echo_msg;

// ros::Publisher float_pub("float_topic", &float_msg);
// ros::Publisher bool_pub("bool_topic", &bool_msg);
// ros::Publisher int8_pub("echo_topic", &echo_msg);

// 콜백 함수 정의
void int8Callback(const std_msgs::Int8 &int8_msg)
{
  // Int8 메시지를 받았을 때 실행되는 코드
  int8_t received_value = int8_msg.data;
  echo_msg.data = received_value;
  /*
  int8_pub.publish(&echo_msg);
  // 여기에 필요한 작업을 추가하세요.

  // Int8 값을 float32로 변환하여 publish
  float_msg.data = static_cast<float>(received_value);
  float_pub.publish(&float_msg);

  // Int8 값을 bool로 변환하여 publish
  bool_msg.data = (received_value > 0) ? true : false;
  bool_pub.publish(&bool_msg);
  */
}

// 토픽 선언
ros::Subscriber<std_msgs::Int8> int8_sub("command", int8Callback);
#endif

void setup()
{
  // 노드 초기화
  nh.initNode();

  // 토픽에 대한 구독자 및 발행자 등록
  nh.subscribe(int8_sub);
  // nh.advertise(float_pub);
  // nh.advertise(bool_pub);
  // nh.advertise(int8_pub);

  setupAcc();
  setUpLinear();
}

void loop()
{
  // ROS 이벤트 처리
  nh.spinOnce();

// 추가적인 작업이 필요한 경우 여기에 추가하세요.
#ifdef RELEASE
  int8_t command = echo_msg.data;
  if (command == 4) // UP_FRONT_WHEEL
  {
    setUpForward();
    AccelLinear(150);
    nh.loginfo("UP_REAR_WHEEL");
  }
  else if (command == 0)
  { // STOP
    setStop();
    StopLinear();
    nh.loginfo("STOP");
  }
  else if (command == 1)
  { //"START"
    setForward();
    Accel(255);
    nh.loginfo("START");
  }
  else if (command == 5)
  {
    setDownForward();
    AccelLinear(150);
    nh.loginfo("DOWN_REAR_WHEEL");
  }
  else if (command == 6)
  {
    setForward();
    setUpForward();
    Accel(255);
    AccelLinear(150);
    nh.loginfo("ESCAPE_REAR_WHEEL");
  }
  else if (command == 7)
  {
    setForward();
    Accel(255);
    nh.loginfo("INTO_REAR_WHEEL");
  }
  else if (command == 8)
  {
    setBackward();
    Accel(255);
  }

  // pitch_msg.data = getPitch();
  // rps_msg.data = getRPS();
#endif

  // 일정한 간격으로 loop를 실행하려면 delay를 사용하세요.
  delay(100);
}
