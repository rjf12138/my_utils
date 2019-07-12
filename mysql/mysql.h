#ifndef __MYSQL_H__
#define __MYSQL_H__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define MYSQLPP_MYSQL_HEADERS_BURIED

#include <mysql++/mysql++.h>

#define DATABASE_FILE_PATH                  "user_database_file_path"
#define FRIENDS_UPPER_LIMIT                 "max_friend_a_user_can_hold"
#define GROUP_MEMBER_UPPER_LIMIT            "max_member_a_group_can_hold"


// 数据库表的类型
enum table_type {
    USER_TABLE,
    USER_FRIEND_TABLE,
    GROUP_TABLE,
    GROUP_MEMBER_TABLE,
    USER_JOINED_GROUP_TABLE,
    USER_MANAGERED_GROUP_TABLE
};

struct database_table {
    table_type value_type;                   // table 表示传入数据对应的什么表
    struct {
        std::string account;                    // 用户账号
        std::string name;                       // 用户名
        std::string password;                   // 用户密码
        std::string signature;                  // 用户签名
        std::string mail;                       // 用户邮箱
        std::string birthday;                   // 用户生日
        std::string head_portrait;              // 用户头像
    } user;                             // 用户数据表

    struct {
        std::string user_account;               // 用户账号
        std::string friend_account;             // 好友账号
    } user_friend;                      // 用户好友表

    struct {
        std::string account;                    // 群账号
        std::string name;                       // 群名称
        std::string manager_account;            // 管理员账号
        std::string introduction;               // 群介绍
        std::string head_portrait;              // 群头像
    } group;                            // 群表

    struct {
        std::string group_account;              // 群账号
        std::string member_account;             // 群成员账号
    } group_member;                     // 群和群成员表

    struct {
        std::string user_account;               // 用户账号
        std::string group_account;              // 用户加入的群账号
    } user_joined_group;                // 用户所加入的群

    struct {
        std::string manager_account;            // 用户账号
        std::string group_account;              // 用户管理的群
    } user_managed_group;             // 用户管理的群 （群主）

    friend std::ostream& operator<<(std::ostream& p_os, const database_table& p_table);
};

class MysqlTest {
public:
    MysqlTest(const std::string& p_database_name, const std::string& p_database_server_ip, 
                const std::string& p_user_account, const std::string& p_user_password);      // MysqlTest 构造函数

#ifdef __MYSQL_TEST__
    mysqlpp::Connection& get_mysqlpp_connector(void) {return d_database_connector;}
#endif

    bool is_user_exists(const std::string p_user_account);                                                           // 查询用户是否存在
    bool is_user_friend_exists(const std::string p_user_account, const std::string p_friend_account);                // 查询用户的好友是否存在
    bool is_group_exists(const std::string p_group_account);                                                           // 群是否存在
    bool is_group_member_exists(const std::string p_group_account, const std::string p_member_account);              // 群成员是否存在
    bool check_user_password(const std::string p_user_account, const std::string p_password);                        // 检查用户密码是否正确

    int insert_user_record_to_user_table(struct database_table& p_table);                                           // 插入一条用户数据
    int insert_user_friend_record_to_user_friend_table(struct database_table& p_table);                             // 插入一条用户和好友的数据
    int insert_user_joined_group_record_to_user_joined_group_table(struct database_table& p_table);                 // 插入一条用户参加的群数据
    int insert_group_record_to_group_table(struct database_table& p_table);                                         // 插入一条群数据
    int insert_group_member_record_to_group_member_table(struct database_table& p_table);                           // 插入一条群成员数据
    int insert_user_managered_group_record_to_user_managered_group_table(struct database_table& p_table);           // 插入一条用户是群管理员的数据

    int select_user_from_user_table(const std::string user_account, struct database_table& p_table);                // 从数据库中的用户表中读取用户信息
    int select_all_users_from_user_table(std::vector<struct database_table>& p_users);                              // 从数据库中读取所有用户的信息
    int select_group_from_group_table(const std::string group_account, struct database_table& p_table);             // 从数据库中读取群的信息
    int select_all_groups_from_group_table(std::vector<struct database_table>& p_groups);                           // 从数据库中读取所有群的信息
    int select_users_friends(const std::string p_user_account, std::vector<struct database_table>& p_friends);                // 从数据库中读取用户所有好友账号
    int select_groups_members(const std::string p_group_account, std::vector<struct database_table>& p_members);              // 从数据库中读取群的所有成员
    int select_all_user_managered_groups(const std::string p_manager_account, std::vector<struct database_table>& p_groups);  // 获取所有用户管理的群账号
    int select_all_user_jonined_groups(const std::string p_user_account, std::vector<struct database_table>& p_groups);       // 获取所有用户加入的群账号

    int update_user_name(struct database_table& p_table);           // 更新用户的用户名
    int update_user_password(struct database_table& p_table);       // 更新用户的密码
    int update_user_mail(struct database_table& p_table);           // 更新用户的邮箱
    int update_user_birthday(struct database_table& p_table);       // 更新用户的生日
    int update_user_signature(struct database_table& p_table);      // 更新用户的签名
    int update_group_manager(struct database_table& p_table);       // 更新群组的管理员
    int update_group_name(struct database_table& p_table);          // 更新群的名字
    int update_group_introduction(struct database_table& p_table);  // 更新群的介绍

    int delete_user_from_user_table(const std::string p_user_account);
    int delete_friend_from_user_friend_table(const std::string p_user_account, const std::string p_friend_account);             // 将好友从用户的好友列表中移除
    int delete_member_from_group_member_table(const std::string p_group_account, const std::string p_member_account);           // 将群成员从群成员列表中移除
    int delete_group_from_group_table(const std::string p_group_account);                                                       // 将群从数据库中移除
    int delete_group_from_user_managed_group_table(const std::string p_manager_account, const std::string p_group_account);   // 将群从用户管理的群列表中移除
    int delete_group_from_user_joined_group_table(const std::string p_user_account, const std::string p_group_account);         // 将群从用户加入的群列表中移除

    ~MysqlTest();
private:
    int init_database_tables(void);
private:
    mysqlpp::Connection d_database_connector;
};

#endif