#ifndef FUNC_ARR_H
#define FUNC_ARR_H

#pragma once

#include "parser.h"

#define offset_1 50
#define offset_2 325
#define offset_3 500
#define scale_1 0.001
#define scale_2 0.0015
#define scale_3 02002
#define scale_4 0.01
#define scale_5 0.02
#define scale_6 0.1
#define scale_7 0.2
#define scale_8 0.5
#define scale_9 2

unsigned char vcu_command_1(unsigned char CANN[], double output_array[]);
unsigned char vcu_command_2(unsigned char CANN[], double output_array[]);
unsigned char battery(unsigned char CANN[], double output_array[]);
unsigned char battery_pack_1(unsigned char CANN[], double output_array[]);
unsigned char battery_pack_2(unsigned char CANN[], double output_array[]);
unsigned char cell_voltage(unsigned char CANN[], double output_array[]);
unsigned char cell_temp(unsigned char CANN[], double output_array[]);
unsigned char bms_limit_1(unsigned char CANN[], double output_array[]);
unsigned char bms_limit_2(unsigned char CANN[], double output_array[]);
unsigned char isolation_r(unsigned char CANN[], double output_array[]);
unsigned char battery_information_1(unsigned char CANN[], double output_array[]);
unsigned char battery_information_2(unsigned char CANN[], double output_array[]);
unsigned char battery_information_3(unsigned char CANN[], double output_array[]);
unsigned char battery_information_4(unsigned char CANN[], double output_array[]);
unsigned char bcu_dtc(unsigned char CANN[], double output_array[]);
unsigned char cell_voltage_status(unsigned char CANN[], double output_array[]);
unsigned char cell_temp_status(unsigned char CANN[], double output_array[]);
unsigned char heat_plate_temp_status(unsigned char CANN[], double output_array[]);
unsigned char charging_status(unsigned char CANN[], double output_array[]);
unsigned char charging_socket_temp(unsigned char CANN[], double output_array[]);
unsigned char vcutoins_c_1(unsigned char CANN[], double output_array[]);
unsigned char vcutoins_c_2(unsigned char CANN[], double output_array[]);
unsigned char vcu_s_1(unsigned char CANN[], double output_array[]);
unsigned char vcu_f_1(unsigned char CANN[], double output_array[]);

#endif