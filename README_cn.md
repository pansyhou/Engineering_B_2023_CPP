# 工程cpp版本



## 心愿（目的

1. 实现面向对象编程，具体的应用场景是，不用注册太多回调函数、模块对象化，解耦、一些
2. 订阅发布消息框架实现（这个是我想在c里实现的，但是我懒，有点类似于ROS里的吧。
3. 将BSP对象化？（理论上 就是能将github上开源的代码直接CV，看了稚晖君的，发现有很多开源库都是cpp
4. 主要还是为以后的拓展实现更多接口
5. 原有架构重构，结构体那些还是太乱了（像是
6. 为以后铺垫，哪怕是个人还是以后





## CAN接收

如何写一个通用的？

#### 发送如何组成四个？

电机class里有设置什么什么的函数，我们在创建这个类的时候定义这个电机的PID类型，当然双环也留有单独set speed and set position only

稚晖君的步进电机封装：

```c++
class CtrlStepMotor
{
public:
    enum State
    {
        RUNNING,
        FINISH,
        STOP
    };

    const uint32_t CTRL_CIRCLE_COUNT = 200 * 256;

    CtrlStepMotor(CAN_HandleTypeDef* _hcan, uint8_t _id, bool _inverse = false, uint8_t _reduction = 1,
                  float _angleLimitMin = -180, float _angleLimitMax = 180);

    uint8_t nodeID;
    float angle = 0;
    float angleLimitMax;
    float angleLimitMin;
    bool inverseDirection;
    uint8_t reduction;
    State state = STOP;

    void SetAngle(float _angle);
    void SetAngleWithVelocityLimit(float _angle, float _vel);
    // CAN Command
    void SetEnable(bool _enable);
    void DoCalibration();
    void SetCurrentSetPoint(float _val);
    void SetVelocitySetPoint(float _val);
    void SetPositionSetPoint(float _val);
    void SetPositionWithVelocityLimit(float _pos, float _vel);
    void SetNodeID(uint32_t _id);
    void SetCurrentLimit(float _val);
    void SetVelocityLimit(float _val);
    void SetAcceleration(float _val);
    void SetDceKp(int32_t _val);
    void SetDceKv(int32_t _val);
    void SetDceKi(int32_t _val);
    void SetDceKd(int32_t _val);
    void ApplyPositionAsHome();
    void SetEnableOnBoot(bool _enable);
    void SetEnableStallProtect(bool _enable);
    void Reboot();
    void EraseConfigs();

    void UpdateAngle();
    void UpdateAngleCallback(float _pos, bool _isFinished);


    // Communication protocol definitions
    auto MakeProtocolDefinitions()
    {
        return make_protocol_member_list(
            make_protocol_ro_property("angle", &angle)
            ...
        );
    }


private:
    CAN_HandleTypeDef* hcan;
    uint8_t canBuf[8] = {};
    CAN_TxHeaderTypeDef txHeader = {};
};
```

发送的时候，直接利用Chassis类里的几个Motor.out数据将发送底盘电机控制信息打包成一个CAN包即可，这样，发送频率可以由自己的主任务频率控制

不用消息框架作为发送主要还是怕没消息来，或者是发送频率不可控，要等spin lock到

#### 接收？

我他码直接将CAN201减去201换成数组index即可（chassis类里有定义8个电机，一开始先设为nullptr。



