#ifndef ENGINEERING_B_2023_C_BOARD_MAIN_TASK_H
#define ENGINEERING_B_2023_C_BOARD_MAIN_TASK_H
#include "Main_Task.h"

/**
 * µ◊≈Ã¿‡–Õ√∂æŸ
 */
typedef enum Chassis_Type
{
    MecanumWheels = 1,
    Chassis_Type_end
}Chassis_Type;

class Chassis {
public:
    explicit Chassis(Chassis_Type type);
    ~Chassis();





};







#endif //ENGINEERING_B_2023_C_BOARD_MAIN_TASK_H
