#define _CRT_SECURE_NO_WARNINGS

#include "parser.h"
#include "func_arr.h"
#include "convert_data.h"
#include "QueueADT.h"
#include <math.h>
#include <stdlib.h>
#include <io.h>
#include <Windows.h>
#include <sysinfoapi.h>

struct _finddata_t fd;

int isFileOrDir()
{
	if (fd.attrib & _A_SUBDIR)
		return 0;
	else
		return 1;
}

void FileSearch(char file_path[])
{
	intptr_t handle;
	int check = 0;
	char file_path2[_MAX_PATH];

	strcat(file_path, "\\");
	strcpy(file_path2, file_path);
	strcat(file_path, "*");

	if ((handle = _findfirst(file_path, &fd)) == -1)
	{
		printf("No such file or directory\n");
		return;
	}

	while (_findnext(handle, &fd) == 0)
	{
		char file_pt[_MAX_PATH];
		strcpy(file_pt, file_path2);
		strcat(file_pt, fd.name);

		check = isFileOrDir();

		if (check == 0 && fd.name[0] != ',')
		{
			FileSearch(file_pt);
		}
		else if (check == 1 && fd.size != 0 && fd.name[0] != ',')
		{
			printf("파일명 : %s, 크기 : %d\n", file_pt, fd.size);
		}
	}
	_findclose(handle);
}


char* CAN_IDs[24] = { "18FFA0F3", "18FFB0F3", "18FFA1F3", "18FFA2F3", "18FFA3F3", "18FFA4F3", "18FFA5F3", "18FFA6F3",
					"18FFA7F3", "18FFA8F3", "18FFA9F3", "18FFAAF3", "18FFACF3", "18FFAFF3", "18FECAF3", "1820F8F4",
					"1880F8F4", "189FF8F4", "18FFC0F3", "18FEC0F3", "1810A6A0", "1811A6A0", "08F200A0", "041000A0" };

int find_index(char* id)
{
	for (int i = 0; i < 24; i++)
	{
		if (strcmp(CAN_IDs[i], id) == 0)
			return i;
	}
	return -1;
}

void tokenizer_DATA(Node* ptr_node)
{
	ptr_node->date = _strdup(strtok(ptr_node->expression, " "));
	ptr_node->time = _strdup(strtok(NULL, " "));
	ptr_node->latitude = _strdup(strtok(NULL, " "));
	ptr_node->longitude = _strdup(strtok(NULL, " "));
	ptr_node->velocity = _strdup(strtok(NULL, " "));
}

void tokenizer_CAN(char* tokenizer_data, Node* ptr_node)
{
	char* temp1, * temp2;

	temp1 = strtok(tokenizer_data, "x");
	temp1 = strtok(NULL, " ");

	ptr_node->CAN_ID = _strdup(temp1);

	temp2 = strtok(NULL, "\n");
	ptr_node->CAN_DATA =_strdup(temp2);

}

Node* create_node()
{
	Node* ptr_node = (Node*)malloc(sizeof(Node));
	if (ptr_node == NULL)
		return;
	else
	{
		ptr_node->date = '0';
		ptr_node->time = NULL;
		ptr_node->expression = '0';
		ptr_node->latitude = 0;
		ptr_node->longitude = 0;
		ptr_node->velocity = 0;
	}

	return ptr_node;
}

int main()
{
	/*char file_path[_MAX_PATH] = "C:";
	FileSearch(file_path);*/

	ULONGLONG start_time = GetTickCount64();

	int index = 0;
	char version[MAX];
	char data_line[MAX];
	char car_number[MAX];
	char boot_time[MAX];
	unsigned char CAN[8];
	double* output_arr;


	unsigned char (*func_array[24])(unsigned char*, double*);
	func_array[0] = zero;
	func_array[1] = one;
	func_array[2] = two;
	func_array[3] = three;
	func_array[4] = four;
	func_array[5] = five;
	func_array[6] = six;
	func_array[7] = seven;
	func_array[8] = eight;
	func_array[9] = nine;
	func_array[10] = ten;
	func_array[11] = eleven;
	func_array[12] = twelve;
	func_array[13] = thirteen;
	func_array[14] = fourteen;
	func_array[15] = fifteen;
	func_array[16] = sixteen;
	func_array[17] = seventeen;
	func_array[18] = eighteen;
	func_array[19] = nineteen;
	func_array[20] = twenty;
	func_array[21] = twentyone;
	func_array[22] = twentytwo;
	func_array[23] = twentythree;

	FILE* data_file[9];
	FILE* wfile = fopen("mydata.csv", "w");

	data_file[0] = fopen("2022-12-22 15.24.24.064 2022-12-22 15.24.24.409.csv", "r");
	data_file[1] = fopen("2022-12-22 15.24.24.064 2022-12-22 15.33.56.244.csv", "r");
	data_file[2] = fopen("2022-12-22 15.24.24.064 2022-12-22 15.43.13.365.csv", "r");
	data_file[3] = fopen("2022-12-22 15.24.24.064 2022-12-22 15.52.31.439.csv", "r");
	data_file[4] = fopen("2022-12-22 15.24.24.064 2022-12-22 16.01.50.527.csv", "r");
	data_file[5] = fopen("2022-12-22 15.24.24.064 2022-12-22 16.11.07.602.csv", "r");
	data_file[6] = fopen("2022-12-22 15.24.24.064 2022-12-22 16.20.23.668.csv", "r");
	data_file[7] = fopen("2022-12-22 15.24.24.064 2022-12-22 16.29.39.725.csv", "r");
	data_file[8] = fopen("2022-12-22 15.24.24.064 2022-12-22 16.38.54.812.csv", "r");


	if (data_file == NULL)
	{
		printf("FIle open Error.");
		return 0;
	}

	char* titleArr[204] = { "boot_time", " collect_time", "gps_latitude", "gps_longitude", "vehicle_speed", "vc1_contactor_request",
"vc1_power_down_request", "vc1_fault_lockout_request", "vc1_ac_precharge_voltage_request","vc1_reserve", "vc1_mcu_input_voltage",
"vc1_motor_ac_current", "vc2_ac_precharge_voltage_status", "batt_status", "batt_mode", "batt_fault_status", "batt_balance_lockout_status",
"batt_fault_lockout_status", "batt_soc", "batt_soh", "batt_pack_internal_resistance", "batt_pack_residual_capacity", "batt_message_counter",
"bp1_vbatt", "bp1_vout", "bp1_pack_i", "bp1_pack_power", "bp1_pack_temp", "bp2_slave_control_online1_8", "bp2_slave_control_online9_16",
"bp2_slave_control_online17_24", "bp2_slave_control_online25_32", "bp2_battery_box_number", "bp2_slave_control_number", "cv_sum",
"cv_max_v", "cv_min_v", "cv_max_v_no", "cv_min_v_no", "cv_max_v_system_no", "cv_min_v_system_no", "ct_avg_temp", "ct_max_temp",
"ct_min_temp", "ct_max_temp_no", "ct_min_temp_no", "ct_max_temp_system_no", "ct_min_temp_system_no", "bl1_max_pack_v", "bl1_min_pack_v",
"bl1_max_cell_v", "bl1_min_cell_v", "bl1_discharge_current", "bl1_max_charge_current", "bl2_max_soc", "bl2_min_soc", "bl2_max_10sec_discharge_power",
"bl2_max_10sec_charge_power", "bl2_max_cell_temp", "bl2_min_cell_temp", "ir_life_signal", "ir_resistance_status", "ir_fault_level",
"ir_rgnd_pos", "ir_rgnd_neg", "bi1_subsystem_count", "bi1_total_cell_count", "bi1_temp_sensor_count", "bi1_system_error_count",
"bi1_charging_status", "bi1_charging_gun_connect", "bi2_subsystem_frame_serial_number", "bi2_subsystem_number", "bi2_code_length",
"bi2_system_code", "bi3_manufacturer", "bi3_nominal_capacity", "bi3_nominal_voltage", "bi3_total_energy", "bi3_cooling_type",
"bi3_system_type", "bi3_bms_protocol_ver", "bi4_accumulated_output_energy", "bi4_accumulated_charge_energy", "bi4_accumulated_regenerative_braking_energy",
"bd_w_cell_uvp", "bd_w2_cell_uvp", "bd_f_cell_uvp", "bd_w_cell_ovp", "bd_w2_cell_ovp", "bd_f_cell_ovp", "bd_w_total_volt_collectfail_level2",
"bd_w_cell_volt_collectfail_level3", "bd_w_cell_utp", "bd_w2_cell_utp", "bd_f_cell_utp", "bd_w_cell_otp", "bd_w2_cell_otp", "bd_f_cell_otp",
"bd_w_temp_channelfail_level2", "bd_w_balance_channelfail_level1", "bd_w_pack_upv", "bd_w2_pack_upv", "bd_f_pack_upv", "bd_w_pack_opv",
 "bd_w2_pack_opv", "bd_f_pack_opv", "bd_w_precharge_relay_adhesionfail_level3", "bd_w_precharge_relay_failurefail_level3", "bd_w_pack_volt_diff",
 "bd_w2_pack_volt_diff", "bd_f_pack_volt_diff", "bd_w_pack_temp_diff", "bd_w2_pack_temp_diff", "bd_w_current_collect_fault", "bd_w_main_relay_plus_adhesionfail_level3",
 "bd_w_main_relay_minus_adhesionfail_level3", "bd_w_under_soc", "bd_w2_under_soc", "bd_f_under_soc", "bd_w_over_soc", "bd_w2_over_soc",
 "bd_f_over_soc", "bd_w_bms_internal_commfail_level3", "bd_w_bms_vehicle_commfail_level3", "bd_w_discharge_ocp", "bd_w2_discharge_ocp",
 "bd_f_discharge_ocp", "bd_w_charge_ocp", "bd_w2_charge_ocp", "bd_f_charge_ocp", "bd_w_insulationfail_level2", "bd_w_insulationfail_level3",
 "bd_w_motor_relay_adhesionfail_level3", "bd_w_discharge_freeze_circuit_breakingfail_level2", "bd_w_charge_freeze_circuit_breakingfail_level2",
 "bd_w_fast_charge_relay_adhesionfail_level3", "bd_w_slow_charge_relay_adhesionfail_level3", "bd_w_heat_relay_adhesionfail_level3",
 "bd_w_sock_jump_abnormal", "bd_w_batt_system_mismatch", "bd_w_fast_charge_anode_hightempclass2", "bd_w_fast_charge_anode_hightempclass3",
 "bd_w_fast_charge_cathode_hightempclass2", "bd_w_fast_charge_cathode_hightempclass3", "bd_w_slow_charge_anode_hightempclass2",
 "bd_w_slow_charge_anode_hightempclass3", "bd_w_slow_charge_cathode_hightempclass2", "bd_w_slow_charge_cathode_hightempclass3",
 "cvs_box_number", "cvs_series_number", "cvs_voltage1", "cvs_voltage2", "cvs_voltage3", "cvs_voltage4", "cts_sensing_box_number",
  "cts_sensing_number", "cts_sensing1", "cts_sensing2", "cts_sensing3", "cts_sensing4", "cts_sensing5", "cts_sensing6", "hpts_sensing_box_number",
  "hpts_sensing_number", "hpts_sensing1", "hpts_sensing2", "hpts_sensing3", "hpts_sensing4", "hpts_sensing5", "hpts_sensing6", "cs_quick_cc2_resistance",
  "cs_slow_cc_resistance", "cs_slow_charge_pwm", "cs_digital_lock_status", "cs_s2_switch_status", "cst_ac_l_temp", "cst_ac_n_temp",
  "cst_dc_p_temp", "cst_dc_n_temp", "cst_ac_l_temp_status", "cst_ac_n_temp_status", "cst_dc_p_temp_status", "cst_dc_n_temp_status",
  "vic1_battery_soc_ins", "vic1_battery_current_ins", "vic1_battery_volt_ins", "vic1_insul_resistance", "vic1_cell_max_temp", "vic1_led_charge_cmd",
  "vic1_led_charge_connect_cmd", "vic1_led_vehicle_insulation_warn", "vic1_led_battery_low_voltage_warn", "vic1_led_low_soc_temp_warn",
  "vic1_led_battery_failure", "vic1_led_sound_signal", "vic2_ready_signal", "vs1_vehicle_function", "vs1_shift_location", "vs1_key_status",
  "vs1_vehicle_speed", "vs1_pedal_state", "vs1_brake_state", "vf1_handbrake_status" };

	for (int i = 0; i < 204; i++)
		fprintf(wfile, "%s,", titleArr[i]);

	fprintf(wfile, "\n");


	for (int n = 0; n < 9; n++)
	{
		Queue* q = create_queue();

		fgets(version, MAX, data_file[n]);
		fgets(car_number, MAX, data_file[n]);
		fgets(boot_time, MAX, data_file[n]);
		strcpy(boot_time, strtok(boot_time, "\n"));

		fgets(data_line, MAX, data_file[n]);	//2022-12-22 15:33:50.242 35.690048 128.445999 2.6 0x08F200A0 01 2A 00 00 00 39 22 00



		while (strcmp(data_line, "\n") != 0)
		{

			output_arr = calloc(199, sizeof(double));

			Node* node = (Node*)malloc(sizeof(Node));
			if (node == NULL)
				return;

			node->expression = _strdup(data_line);

			tokenizer_DATA(node);




			while (strcmp(data_line, "\n") != 0)
			{

				char data_line_dup[MAX];
				strcpy(data_line_dup, data_line);
				tokenizer_CAN(data_line_dup, node);

				Parser(node, CAN);

				index = find_index(node->CAN_ID);

				if (index != -1)
				{

					func_array[index](CAN, output_arr);

					fgets(data_line, MAX, data_file[n]);
					continue;
				}
				else if (index == -1)
				{
					fgets(data_line, MAX, data_file[n]);
				}
				//문단 끝

				fgets(data_line, MAX, data_file[n]);
			}

			enqueue(q, output_arr, node);

			fgets(data_line, MAX, data_file[n]);
		}

		dequeue(q, wfile, boot_time);

		free(q);

		fclose(data_file[n]);

	}
	fclose(wfile);

	// Task //

	ULONGLONG end_time = GetTickCount64();
	long double interval_time = (double)(end_time - start_time) / 1000;
	printf("%lf\n", interval_time);

	return 0;
}