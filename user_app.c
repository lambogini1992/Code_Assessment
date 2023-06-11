#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define FILE_KERNEL_PATH            "/dev/invert_dev"

static int  read_device_file(uint8_t *str_buf, size_t buf_size);
static int  write_device_file(uint8_t *str_buf, size_t buf_size);
static char *read_data_file(char *filename, size_t *fl_size);
static void data_file_freebuf(char *buf);

int main(int argc, char *argv[])
{
    char        *input_str = NULL;
    uint8_t     *p_rbuf = NULL;
    size_t      str_size = 0;
    int ret = 0;
    if(argc < 2)
    {
        printf("Please input file path with command format:\r\n");
        printf("\t\t user_app <FILE_PATH>");
        return -1;
    }
    
    input_str = read_data_file(argv[1], &str_size);
    if(NULL == input_str)
    {
        return -1;
    }

    if(-1 == write_device_file(input_str, str_size))
    {
        return -1;
    }
    read_device_file(p_rbuf, str_size);
    printf("Invert String output: %s\r\n", p_rbuf);
    free(p_rbuf);
    free(input_str);
    return 0;
}

static void data_file_freebuf(char *buf)
{
    if(buf)
    {
        free(buf);
    }
}

static char *read_data_file(char *filename, size_t *fl_size)
{
    FILE *p_file = NULL;
    char *r_buf  = NULL;
    size_t file_size = 0;
    int ret      = 0;

    p_file = fopen(filename, "r");
    if(NULL == p_file)
    {
        printf("Failed to open file\r\n");
        return NULL;
    }

    fseek(p_file, 0, SEEK_END);
    file_size = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);
    
    if(0 == file_size)
    {
        printf("File size is O\r\n");
        return NULL;
    }

    r_buf = (char *)malloc(file_size);

    ret = fread(r_buf, sizeof(uint8_t), file_size, p_file);
    if(ret != file_size)
    {
        printf("Failed to read file\r\n");
        free(r_buf);
        r_buf = NULL;
    }
    else
    {
        *fl_size = file_size;
    }

    fclose(p_file);
    
    return r_buf;
}

static int  read_device_file(uint8_t *str_buf, size_t buf_size)
{
    FILE *p_file = NULL;
    int ret = 0;
    p_file = fopen(FILE_KERNEL_PATH, "r");
    if(NULL == p_file)
    {
        printf("Failed to open file\r\n");
        return -1;
    }

    ret = fread(str_buf, sizeof(uint8_t), buf_size, p_file);
    if(ret != buf_size)
    {
        printf("Failed to read file\r\n");
        ret = -1;
    }

    fclose(p_file);
    return ret;
}

static int  write_device_file(uint8_t *str_buf, size_t buf_size)
{
    FILE *p_file = NULL;
    int ret = 0;
    p_file = fopen(FILE_KERNEL_PATH, "w");
    if(NULL == p_file)
    {
        printf("Failed to open file\r\n");
        return -1;
    }

    ret = fwrite(str_buf, sizeof(uint8_t), buf_size, p_file);
    if(ret != buf_size)
    {
        printf("Failed to write file\r\n");
        ret = -1;
    }

    fclose(p_file);
    return ret;
}
