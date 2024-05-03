#include <tools/logger.h>

void logger_log_generic(char* type, char* msg, usize msg_len);

void logger_info(char* buf, usize count) {
    logger_log_generic("\033[1;94m[ INFO ]\033[0m ", buf, count);
}

void logger_success(char* buf, usize count) {
    logger_log_generic("\033[1;92m[  OK  ]\033[0m ", buf, count);
}

void logger_warn(char* buf, usize count) {
    logger_log_generic("\033[1;93m[ WARN ]\033[0m ", buf, count);
}

void logger_error(char* buf, usize count) {
    logger_log_generic("\033[1;91m[ FAIL ]\033[0m ", buf, count);
}

void logger_log_generic(char* type, char* msg, usize msg_len) {
    serial_send(type);
    serial_send(msg);
    serial_send("\n");

    flanterm_write(flanterm_context, type, 20);
    flanterm_write(flanterm_context, msg, msg_len);
    flanterm_write(flanterm_context, "\n", 1);
}