#include <serverview.h>
#include <stdio.h>

void server_login_menu(void)
{
	printf("1.管理员登录\n");
	printf("2.关闭系统\n");
}

void server_main_menu(void)
{
	printf("1.启动服务器\n");
	printf("2.服务器状态\n");
	printf("3.增开服务器\n");
	printf("4.重启服务器\n");
	printf("5.关闭服务器\n");
	printf("6.注销\n")
}
void server_user_message_menu(void)
{
	printf("1.用户信息\n");
	printf("2.用户排序\n");
	printf("3.冻结用户\n");
	printf("4.解冻用户\n");
	printf("5.返回主页\n");
}
