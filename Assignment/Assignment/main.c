#define _CRT_SECURE_NO_WARNINGS

#include "parser.h"
#include "func_arr.h"
#include "convert_data.h"
#include "QueueADT.h"
#include "search_file.h"
#include <math.h>
#include <stdlib.h>
#include <sysinfoapi.h>

#define csv_file_num 9
#define title_num 204

int main()
{
	ULONGLONG start_time = GetTickCount64();

	double* output_arr;
	int index = 0;
	char version[MAX];
	char data_line[MAX];
	char car_number[MAX];
	char boot_time[MAX];
	char file_path[_MAX_PATH] = "C:\\can_data";
	unsigned char parsed_can_data[8];
	
	FILE* wfile = fopen("mydata.csv", "w");
	FILE* csv_data_file[9];
	file_search(file_path, csv_data_file);

	unsigned char (*func_array[24])(unsigned char*, double*);
	func_array[0] = vcu_command_1;
	func_array[1] = vcu_command_2;
	func_array[2] = battery;
	func_array[3] = battery_pack_1;
	func_array[4] = battery_pack_2;
	func_array[5] = cell_voltage;
	func_array[6] = cell_temp;
	func_array[7] = bms_limit_1;
	func_array[8] = bms_limit_2;
	func_array[9] = isolation_r;
	func_array[10] = battery_information_1;
	func_array[11] = battery_information_2;
	func_array[12] = battery_information_3;
	func_array[13] = battery_information_4;
	func_array[14] = bcu_dtc;
	func_array[15] = cell_voltage_status;
	func_array[16] = cell_temp_status;
	func_array[17] = heat_plate_temp_status;
	func_array[18] = charging_status;
	func_array[19] = charging_socket_temp;
	func_array[20] = vcutoins_c_1;
	func_array[21] = vcutoins_c_2;
	func_array[22] = vcu_s_1;
	func_array[23] = vcu_f_1;

	char* can_message_id_[title_num] = { "boot_time", " collect_time", "gps_latitude", "gps_longitude", "vehicle_speed", "vc1_contactor_request",
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

	for (int i = 0; i < title_num; i++) {
		fprintf(wfile, "%s,", can_message_id_[i]);
	}
	fprintf(wfile, "\n");

	for (int n = 0; n < csv_file_num; n++) {

		Queue* q = create_queue();

		fgets(version, MAX, csv_data_file[n]);
		fgets(car_number, MAX, csv_data_file[n]);
		fgets(boot_time, MAX, csv_data_file[n]);
		strcpy(boot_time, strtok(boot_time, "\n"));
		fgets(data_line, MAX, csv_data_file[n]);	//data_line = "2022-12-22 15:33:50.242 35.690048 128.445999 2.6 0x08F200A0 01 2A 00 00 00 39 22 00"

		while (strcmp(data_line, "\n") != 0) {
			output_arr = calloc(row_num, sizeof(double));

			Node* node = create_node();
			node->expression = _strdup(data_line);
			tokenizer_data(node);

			while (strcmp(data_line, "\n") != 0) {
				char data_line_dup[MAX];

				strcpy(data_line_dup, data_line);
				tokenizer_can(data_line_dup, node);
				parser(node, parsed_can_data);

				index = find_index(node->can_id);
				if (index != -1) {
					func_array[index](parsed_can_data, output_arr);

					fgets(data_line, MAX, csv_data_file[n]);
					continue;
				}
				else if (index == -1) {
					fgets(data_line, MAX, csv_data_file[n]);
				}
				fgets(data_line, MAX, csv_data_file[n]);
			}
			enqueue(q, output_arr, node);
			fgets(data_line, MAX, csv_data_file[n]);
		}
		dequeue(q, wfile, boot_time);
		free(q);
		fclose(csv_data_file[n]);
	}
	fclose(wfile);

	ULONGLONG end_time = GetTickCount64();
	long interval_time = (end_time - start_time);
	printf("%d ms\n", interval_time);

	return 0;
}