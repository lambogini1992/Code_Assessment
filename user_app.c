#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define FILE_KERNEL_PATH            "/dev/invert_dev"

static int  read_device_file(uint8_t *str_buf, size_t buf_size);
static int  write_device_file(uint8_t *str_buf, size_t buf_size);

int main(int argc, char *argv[])
{
    char        *input_str = NULL;
    uint8_t     *p_rbuf = NULL;
    size_t      str_size = 0;
    int ret = 0;
    if(argc < 2)
    {
        printf("Please input string with command format:\r\n");
        printf("\t\t user_app <STRING_INPUT>");
        return -1;
    }
    
    for(int idx = 1; idx < argc; idx++)
    {
        //For space character
        str_size += (strlen((char *)argv[idx]) + 1);
    }

    input_str = (uint8_t *)malloc(str_size + 1);
    input_str[0] = 0;
    for(int idx = 1; idx < argc; idx++)
    {
        sprintf(input_str,"%s %s",input_str,argv[idx]);
    }


    p_rbuf   = (uint8_t *)malloc(str_size + 1);

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
