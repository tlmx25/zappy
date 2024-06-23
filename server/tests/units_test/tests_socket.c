/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_socket
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "server.h"


static void open_write_in_file(void)
{
    int fd = open("test.txt", O_CREAT | O_WRONLY, 0666);
    if (fd == -1)
        cr_assert_fail("error open\n");

    write(fd, "Hello\n", 6);
    close(fd);
}

static void delete_file(void)
{
    remove("test.txt");
}

Test(read_socket, read_socket)
{
    open_write_in_file();
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        cr_assert_fail("error open\n");

    char *buffer = read_socket(fd);
    cr_assert_str_eq(buffer, "Hello\n");
    free(buffer);
    close(fd);
    delete_file();
}

Test(write_socket, write_socket)
{
    int fd = open("test.txt", O_CREAT | O_WRONLY, 0666);
    if (fd == -1)
        cr_assert_fail("error open\n");

    write_socket(fd, "Hello\n");
    close(fd);

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        cr_assert_fail("error open\n");

    char *buffer = read_socket(fd);
    cr_assert_str_eq(buffer, "Hello\n");
    free(buffer);
    close(fd);
    delete_file();
}