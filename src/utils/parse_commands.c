#define _DEFAULT_SOURCE
#include <string.h>
#include <stdlib.h>


// Function to parse command and arguments with support for single quotes, double quotes, backslash escaping, and concatenation
int parse_command(char *input, char **args, int max_args) {
    int arg_count = 0;
    int i = 0;
    int len = strlen(input);
    
    while (i < len && arg_count < max_args - 1) {
        // Skip leading whitespace
        while (i < len && input[i] == ' ') {
            i++;
        }
        if (i >= len) break;

        // Start a new argument buffer
        char arg_buf[256];
        int buf_pos = 0;
        int in_arg = 0;

        while (i < len && input[i] != ' ') {
            if (input[i] == '\\') {
                // Handle backslash escaping
                i++; // Skip the backslash
                if (i < len) {
                    // Add the escaped character literally
                    if (buf_pos < 255) {
                        arg_buf[buf_pos++] = input[i];
                    }
                    i++;
                }
                in_arg = 1;
            } else if (input[i] == '\'') {
                // Handle single-quoted segment
                i++; // Skip opening quote
                while (i < len && input[i] != '\'') {
                    if (buf_pos < 255) {
                        arg_buf[buf_pos++] = input[i];
                    }
                    i++;
                }
                if (i >= len) {
                    // Unterminated quote
                    return -1;
                }
                i++; // Skip closing quote
                in_arg = 1;
            } else if (input[i] == '"') {
                // Handle double-quoted segment with special escaping rules
                i++; // Skip opening quote
                while (i < len && input[i] != '"') {
                    if (input[i] == '\\') {
                        // Handle backslash within double quotes
                        i++; // Skip the backslash
                        if (i < len) {
                            char next_char = input[i];
                            // Only escape specific characters: ", \, $, `, newline
                            if (next_char == '"' || next_char == '\\' || next_char == '$' || next_char == '`' || next_char == '\n') {
                                // Add the escaped character literally
                                if (buf_pos < 255) {
                                    arg_buf[buf_pos++] = next_char;
                                }
                            } else {
                                // For other characters, add backslash and the character
                                if (buf_pos < 255) {
                                    arg_buf[buf_pos++] = '\\';
                                }
                                if (buf_pos < 255) {
                                    arg_buf[buf_pos++] = next_char;
                                }
                            }
                            i++;
                        }
                    } else {
                        // Regular character within double quotes
                        if (buf_pos < 255) {
                            arg_buf[buf_pos++] = input[i];
                        }
                        i++;
                    }
                }
                if (i >= len) {
                    // Unterminated quote
                    return -1;
                }
                i++; // Skip closing quote
                in_arg = 1;
            } else {
                // Handle unquoted segment
                while (i < len && input[i] != ' ' && input[i] != '\'' && input[i] != '"' && input[i] != '\\') {
                    if (buf_pos < 255) {
                        arg_buf[buf_pos++] = input[i];
                    }
                    i++;
                }
                in_arg = 1;
            }
        }
        if (in_arg) {
            arg_buf[buf_pos] = '\0';
            args[arg_count++] = strdup(arg_buf); // Use strdup to allocate memory
        }
    }
    args[arg_count] = NULL;
    return arg_count;
}