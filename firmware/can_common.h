// We have a bit of a mess with too many useful usages of CAN and too little documentation at https://github.com/rusefi/rusefi/wiki/CAN

// we use ExtID but only 16 bits in comms protocol from ECU to GDI4
#define GDI4_BASE_ADDRESS 0xBB20

// 0x10 IDs are used for input
// 0x10 IDs are used for output
#define GDI4_BASE_ADDRESS_OFFSET	0x20

#define GDI4_MAGIC 0x67

#define GDI4_CAN_SET_TAG 0x78
#define GDI4_CAN_SET_DLC 7

#define BENCH_TEST_BASE_ADDRESS 0x770000

enum class bench_test_packet_ids_e : int32_t {
	// ECU output
	EVENT_COUNTERS = BENCH_TEST_BASE_ADDRESS,
	// ECU output
	RAW_ANALOG_1,
	// ECU input special bench quality control mode, not to be confused with ECU_CAN_BUS_USER_CONTROL
	HW_QC_IO_CONTROL,
	// ECU output
	BOARD_STATUS,
	// ECU output
	BUTTON_COUNTERS, // 0x770004
	// ECU output
	IO_META_INFO,
	// ECU output
	RAW_ANALOG_2,
	// ECU output
	PIN_STATE, // 0x770007
	// ECU output
	AUX_DIGITAL_COUNTERS,
	// ECU output
	MANUAL_PIN_TEST,
	// OpenBLT input 0x77000A
	FW_WIPE_OUT,
	// ECU input 0x77000B
	HW_QC_TESTER_PRESENT,
	// ECU input 0x77000C - user actions to control ECU
	ECU_CAN_BUS_USER_CONTROL,
	// ECU output 0x77000D
	ECU_CONFIG_BROADCAST,
	// ECU input 0x77000E - user actions to change ECU settings
	ECU_CAN_BUS_SETTINGS_CONTROL,
	// ECU input 0x77000F - dash alive status
	DASH_ALIVE,
	// ECU output 0x770010
	ECU_GET_CALIBRATION,
	// ECU input 0x770011
	ECU_SET_CALIBRATION,
	// ECU input 0x770012
	ECU_REQ_CALIBRATION,
};

enum class bench_test_magic_numbers_e : int32_t {
    BENCH_HEADER = 0x66,
};

enum class bench_test_io_control_e : int8_t {
	CAN_BENCH_GET_COUNT,
	CAN_QC_OUTPUT_CONTROL_SET,
	CAN_QC_OUTPUT_CONTROL_CLEAR,
	CAN_BENCH_SET_ENGINE_TYPE,
	CAN_BENCH_EXECUTE_BENCH_TEST,
	CAN_BENCH_QUERY_PIN_STATE,
	CAN_BENCH_START_PIN_TEST,
	CAN_BENCH_END_PIN_TEST,
	CAN_QC_ETB,
};
