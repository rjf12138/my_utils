/*
*
*
*/
#include <iostream>
#include <string>
#include <vector>

#define __MYSQL_TEST__
#include "mysql.h"

enum TEST_RETURN_INFO {
    MYSQLPP_ERROE = 0,
    CANT_FIND_DATA,
    INSERT_FAILED,
    SELECT_FAILED,
    DELETE_FAILED,
    COMPARED_FAILED,
    UNKNOWN_OPTION,
    TEST_SUCCESSED
};

enum SELECT_OPTION {
    SELECT_USER,
    SELECT_USERS,
    SELECT_GROUP,
    SELECT_GROUPS,
    SELECT_USER_FRIENDS,
    SELECT_GROUP_MEMBERS,
    SELECT_USER_JOINED_GROUPS,
    SELECT_USER_MANAGED_GROUPS
};

enum UPDATE_OPTION {
    UPDATE_USER_NAME,
    UPDATE_USERE_PASSWORD,
    UPDATE_USER_MAIL,
    UPDATE_USER_BIRTHDAY,
    UPDATE_USER_SIGNATURE,
    UPDATE_GROUP_MANAGER,
    UPDATE_GROUP_NAME,
    UPDATE_GROUP_INTRODUCTION
};

enum DELETE_OPTION {
    DELETE_USER,
    DELETE_USER_FRIEND,
    DELETE_GROUP_MEMBER,
    DELETE_GROUP,
    DELETE_USER_MANAGED_GROUP,
    DELETE_USER_JOINED_GROUP
};

void    MysqlTest_clear_all_tables(MysqlTest& p_mysql_test_instance);
uint8_t MysqlTest_insert_row_to_table_test(MysqlTest& p_mysql_test_instance, struct database_table& p_table);
uint8_t MysqlTest_select_row_from_table_test(MysqlTest& p_mysql_test_instance, uint8_t p_option, const std::vector<struct database_table>& p_datas);
uint8_t MysqlTest_update_field_in_table_test(MysqlTest& p_mysql_test_instance, uint8_t p_option, const struct database_table& p_datas);
uint8_t MysqlTest_delete_field_in_table_test(MysqlTest& p_mysql_test_instance, uint8_t p_option, const struct database_table& p_datas);

std::string MysqlTest_print_test_result(uint8_t p_ret);

int main(void)
{
    MysqlTest l_mysql_test_instance("test", "127.0.0.1", "root", "123456");
    struct database_table l_table;
    std::vector<struct database_table> l_tables;

    MysqlTest_clear_all_tables(l_mysql_test_instance);

    l_table.value_type = USER_TABLE;
    l_table.user.account = "123456";
    l_table.user.name = "watchdog";
    l_table.user.password = "123456tyu";
    l_table.user.birthday = "1994-09-19";
    std::cout << "test insert user ret: " << MysqlTest_print_test_result(MysqlTest_insert_row_to_table_test(l_mysql_test_instance, l_table)) << std::endl;

    l_table.value_type = GROUP_TABLE;
    l_table.group.account = "123459";
    l_table.group.manager_account = "832134";
    l_table.group.name = "fishing";
    l_table.group.introduction = "ikun";
    std::cout << "test insert group ret: " << MysqlTest_print_test_result(MysqlTest_insert_row_to_table_test(l_mysql_test_instance, l_table)) << std::endl;

    l_table.value_type = GROUP_MEMBER_TABLE;
    l_table.group_member.group_account = "6722";
    l_table.group_member.member_account = "877667";
    std::cout << "test insert group_member ret: " << MysqlTest_print_test_result(MysqlTest_insert_row_to_table_test(l_mysql_test_instance, l_table)) << std::endl;


    l_table.value_type = USER_FRIEND_TABLE;
    l_table.user_friend.user_account = "67743322";
    l_table.user_friend.friend_account = "980877667";
    std::cout << "test insert user_friend ret: " << MysqlTest_print_test_result(MysqlTest_insert_row_to_table_test(l_mysql_test_instance, l_table)) << std::endl;

    l_table.value_type = USER_JOINED_GROUP_TABLE;
    l_table.user_joined_group.user_account = "6774322";
    l_table.user_joined_group.group_account = "7667";
    std::cout << "test insert user_joined_group ret: " << MysqlTest_print_test_result(MysqlTest_insert_row_to_table_test(l_mysql_test_instance, l_table)) << std::endl;

    l_table.value_type = USER_MANAGERED_GROUP_TABLE;
    l_table.user_managed_group.manager_account = "67722";
    l_table.user_managed_group.group_account = "9867";
    std::cout << "test insert user_managed_group ret: " << MysqlTest_print_test_result(MysqlTest_insert_row_to_table_test(l_mysql_test_instance, l_table)) << std::endl;

    
    return 0;
}

void
MysqlTest_clear_all_tables(MysqlTest& p_mysql_test_instance)
{
    auto l_mysqlpp_connector = p_mysql_test_instance.get_mysqlpp_connector();
    mysqlpp::Query l_query = l_mysqlpp_connector.query();

    l_query << "SHOW TABLES;";
    mysqlpp::StoreQueryResult l_res = l_query.store();

    for (int i = 0; i < l_res.size(); ++i) {
        l_query << "SELECT COUNT(*) FROM test." << l_res[i]["Tables_in_test"] << ";";
        mysqlpp::StoreQueryResult t_res = l_query.store();

        if (t_res.begin() == t_res.end()) {
            continue;
        }

        l_query << "TRUNCATE TABLE test." << l_res[i]["Tables_in_test"] << ";";
        l_query.execute();
    }

    return ;
}

std::string
MysqlTest_print_test_result(uint8_t p_ret)
{
    switch (p_ret) {
        case MYSQLPP_ERROE:
            return "MYSQLPP_ERROE";
            break;
        case CANT_FIND_DATA:
            return "CANT_FIND_DATA";
            break;
        case INSERT_FAILED:
            return "INSERT_FAILED";
            break;
        case SELECT_FAILED:
            return "SELECT_FAILED";
            break;
        case DELETE_FAILED:
            return "DELETE_FAILED";
            break;
        case COMPARED_FAILED:
            return "COMPARED_FAILED";
            break;
        case UNKNOWN_OPTION:
            return "UNKNOWN_OPTION";
            break;
        case TEST_SUCCESSED:
            return "TEST_SUCCESSED";
            break;
        default:
            return "Error ret";
            break;
    };
}

uint8_t 
MysqlTest_delete_field_in_table_test(MysqlTest& p_mysql_test_instance, uint8_t p_option, const struct database_table& p_datas)
{
    struct database_table l_table;
    auto l_mysql_connector = p_mysql_test_instance.get_mysqlpp_connector();
    mysqlpp::Query l_query = l_mysql_connector.query();

    switch (p_option) {
        case DELETE_USER:
        {
            l_query << "INSERT INTO user (account, name, birthday) ";
            l_query << "VALUES (" << p_datas.user.account << ", " << p_datas.user.name << ", ";
            l_query << p_datas.user.birthday << ");";
            l_query.execute();

            l_query << "SELECT account FROM user WHERE account = " << p_datas.user.account << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            bool user_is_exist = false;
            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["account"].compare(p_datas.user.account)) {
                    user_is_exist = true;
                }
            }

            if (user_is_exist != true) {
                return MYSQLPP_ERROE;
            }

            p_mysql_test_instance.delete_user_from_user_table(p_datas.user.account);

            l_query << "SELECT account FROM user WHERE account = " << p_datas.user.account << ");";
            t_res = l_query.store();

            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["account"].compare(p_datas.user.account)) {
                    return DELETE_FAILED;
                }
            }
        } break;
        case DELETE_USER_FRIEND:
        {
            l_query << "INSERT INTO user_friend (user_account, friend_account) ";
            l_query << "VALUES (" << p_datas.user_friend.user_account << ", " << p_datas.user_friend.friend_account << ");";
            l_query.execute();

            l_query << "SELECT user_account FROM user_friend WHERE user_account = " << p_datas.user_friend.user_account << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            bool user_is_exist = false;
            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["user_account"].compare(p_datas.user_friend.user_account)) {
                    user_is_exist = true;
                }
            }

            if (user_is_exist != true) {
                return MYSQLPP_ERROE;
            }

            p_mysql_test_instance.delete_friend_from_user_friend_table(p_datas.user_friend.user_account, p_datas.user_friend.friend_account);

            l_query << "SELECT user_account FROM user_friend WHERE user_account = " << p_datas.user_friend.user_account << ");";
            t_res = l_query.store();

            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["user_account"].compare(p_datas.user_friend.user_account)) {
                    return DELETE_FAILED;
                }
            }
        } break;
        case DELETE_GROUP:
        {
            l_query << "INSERT INTO group (account, name, manager_account, introduction) ";
            l_query << "VALUES (" << p_datas.group.account << ", " << p_datas.group.name << ", ";
            l_query << p_datas.group.manager_account << ", " << p_datas.group.introduction << ");";
            l_query.execute();

            l_query << "SELECT account FROM group WHERE account = " << p_datas.group.account << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            bool user_is_exist = false;
            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["account"].compare(p_datas.group.account)) {
                    user_is_exist = true;
                }
            }

            if (user_is_exist != true) {
                return MYSQLPP_ERROE;
            }

            p_mysql_test_instance.delete_group_from_group_table(p_datas.group.account);

            l_query << "SELECT account FROM group WHERE account = " << p_datas.group.account << ");";
            t_res = l_query.store();

            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["account"].compare(p_datas.group.account)) {
                    return DELETE_FAILED;
                }
            }
        } break;
        case DELETE_GROUP_MEMBER:
        {
            l_query << "INSERT INTO group_member (group_account, member_account) ";
            l_query << "VALUES (" << p_datas.group_member.group_account << ", " << p_datas.group_member.member_account << ");";
            l_query.execute();

            l_query << "SELECT group_account FROM group_member WHERE group_account = " << p_datas.group_member.group_account << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            bool user_is_exist = false;
            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["group_account"].compare(p_datas.group_member.group_account)) {
                    user_is_exist = true;
                }
            }

            if (user_is_exist != true) {
                return MYSQLPP_ERROE;
            }

            p_mysql_test_instance.delete_member_from_group_member_table(p_datas.group_member.group_account, p_datas.group_member.member_account);

            l_query << "SELECT group_account FROM group_member WHERE group_account = " << p_datas.group_member.member_account << ");";
            t_res = l_query.store();

            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["group_account"].compare(p_datas.group_member.member_account)) {
                    return DELETE_FAILED;
                }
            }
        } break;
        case DELETE_USER_JOINED_GROUP:
        {
            l_query << "INSERT INTO user_joined_group (user_account, group_account) ";
            l_query << "VALUES (" << p_datas.user_joined_group.user_account << ", " << p_datas.user_joined_group.group_account << ");";
            l_query.execute();

            l_query << "SELECT user_account FROM user_joined_group WHERE user_account = " << p_datas.user_joined_group.user_account << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            bool user_is_exist = false;
            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["user_account"].compare(p_datas.user_joined_group.user_account)) {
                    user_is_exist = true;
                }
            }

            if (user_is_exist != true) {
                return MYSQLPP_ERROE;
            }

            p_mysql_test_instance.delete_group_from_user_joined_group_table(p_datas.user_joined_group.user_account, p_datas.user_joined_group.group_account);

            l_query << "SELECT user_account FROM user_joined_group WHERE user_account = " << p_datas.user_joined_group.user_account << ");";
            t_res = l_query.store();

            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["user_account"].compare(p_datas.user_joined_group.user_account)) {
                    return DELETE_FAILED;
                }
            }
        } break;
        case DELETE_USER_MANAGED_GROUP:
        {
            l_query << "INSERT INTO user_managed_group (manager_account, group_account) ";
            l_query << "VALUES (" << p_datas.user_managed_group.manager_account << ", " << p_datas.user_managed_group.group_account << ");";
            l_query.execute();

            l_query << "SELECT manager_account FROM user_managed_group WHERE manager_account = " << p_datas.user_managed_group.manager_account << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            bool user_is_exist = false;
            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["manager_account"].compare(p_datas.user_managed_group.manager_account)) {
                    user_is_exist = true;
                }
            }

            if (user_is_exist != true) {
                return MYSQLPP_ERROE;
            }

            p_mysql_test_instance.delete_group_from_user_managed_group_table(p_datas.user_managed_group.manager_account, p_datas.user_managed_group.group_account);

            l_query << "SELECT manager_account FROM user_managed_group WHERE manager_account = " << p_datas.user_managed_group.manager_account << ");";
            t_res = l_query.store();

            if (t_res.begin() != t_res.end()) {
                if (t_res[0]["manager_account"].compare(p_datas.user_managed_group.manager_account)) {
                    return DELETE_FAILED;
                }
            }
        } break;
        default:
        {
            return UNKNOWN_OPTION;
        } break;
    };

    return TEST_SUCCESSED;
}

uint8_t 
MysqlTest_update_field_in_table_test(MysqlTest& p_mysql_test_instance, uint8_t p_option, struct database_table& p_datas)
{
    struct database_table l_table;
    auto l_mysql_connector = p_mysql_test_instance.get_mysqlpp_connector();
    mysqlpp::Query l_query = l_mysql_connector.query();

    switch (p_option) {
        case UPDATE_USER_NAME:
        {
            p_mysql_test_instance.update_user_name(p_datas);

            l_query << "SELECT name FROM user WHERE account = " << p_datas.user.account << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            if (t_res[0]["name"].compare(p_datas.user.name) != 0) {
                return COMPARED_FAILED;
            }
        } break;
        case UPDATE_USERE_PASSWORD:
        {
            p_mysql_test_instance.update_user_password(p_datas);

            l_query << "SELECT password FROM user WHERE account = " << p_datas.user.account << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            if (t_res[0]["password"].compare(p_datas.user.password) != 0) {
                return COMPARED_FAILED;
            }
        } break;
        case UPDATE_USER_BIRTHDAY:
        {
            p_mysql_test_instance.update_user_birthday(p_datas);

            l_query << "SELECT birthday FROM user WHERE account = " << p_datas.user.birthday << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            if (t_res[0]["birtday"].compare(p_datas.user.birthday) != 0) {
                return COMPARED_FAILED;
            }
        } break;
        case UPDATE_USER_SIGNATURE:
        {
            p_mysql_test_instance.update_user_signature(p_datas);

            l_query << "SELECT signature FROM user WHERE account = " << p_datas.user.signature << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            if (t_res[0]["signature"].compare(p_datas.user.signature) != 0) {
                return COMPARED_FAILED;
            }
        } break;
        case UPDATE_GROUP_NAME:
        {
            p_mysql_test_instance.update_group_name(p_datas);

            l_query << "SELECT name FROM group WHERE account = " << p_datas.group.name << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            if (t_res[0]["name"].compare(p_datas.group.name) != 0) {
                return COMPARED_FAILED;
            }
        } break;
        case UPDATE_GROUP_MANAGER:
        {
            p_mysql_test_instance.update_group_manager(p_datas);

            l_query << "SELECT manager_account FROM group WHERE account = " << p_datas.group.account << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            if (t_res[0]["manager_account"].compare(p_datas.group.manager_account) != 0) {
                return COMPARED_FAILED;
            }
        } break;
        case UPDATE_GROUP_INTRODUCTION:
        {
            p_mysql_test_instance.update_group_introduction(p_datas);

            l_query << "SELECT introduction FROM group WHERE account = " << p_datas.group.account << ");";
            mysqlpp::StoreQueryResult t_res = l_query.store();

            if (t_res[0]["introduction"].compare(p_datas.group.introduction) != 0) {
                return COMPARED_FAILED;
            }
        } break;
    };

    return TEST_SUCCESSED;
}

uint8_t 
MysqlTest_select_row_from_table_test(MysqlTest& p_mysql_test_instance, uint8_t p_option, const std::vector<struct database_table>& p_datas)
{
    struct database_table l_table;
    std::vector<struct database_table> l_tables;
    auto l_mysql_connector = p_mysql_test_instance.get_mysqlpp_connector();
    mysqlpp::Query l_query = l_mysql_connector.query();
    
    switch (p_option) {
        case SELECT_USER:
        {
            for (int i = 0; i < p_datas.size(); ++i) {
                l_query << "INSERT INTO user (account, name, birthday) ";
                l_query << "VALUES (" << p_datas[i].user.account << ", " << p_datas[i].user.name << ", ";
                l_query << p_datas[i].user.birthday << ");";
                l_query.execute();
            }

            for (int i = 0; i < p_datas.size(); ++i) {
                if (p_mysql_test_instance.select_user_from_user_table(p_datas[i].user.account, l_table) == -1) {
                    return SELECT_FAILED;
                }
                // 比较内容： 用户账号
                if (p_datas[i].user.account.compare(l_table.user.account) != 0) {
                    return COMPARED_FAILED;
                }
                // 比较内容： 用户名
                if (p_datas[i].user.name.compare(l_table.user.name) != 0) {
                    return COMPARED_FAILED;
                }
                // 比较内容： 用户生日
                if (p_datas[i].user.birthday.compare(l_table.user.birthday) != 0) {
                    return COMPARED_FAILED;
                }
            }
        } break;
        case SELECT_USERS:
        {
            for (int i = 0; i < p_datas.size(); ++i) {
                l_query << "INSERT INTO user (account, name, birthday) ";
                l_query << "VALUES (" << p_datas[i].user.account << ", " << p_datas[i].user.name << ", ";
                l_query << p_datas[i].user.birthday << ");";
                l_query.execute();
            }

            if (p_mysql_test_instance.select_all_users_from_user_table(l_tables) == -1) {
                return SELECT_FAILED;
            }

            int i, j;
            for (i = 0; i < p_datas.size(); ++i) {
                for (j = 0; j < l_tables.size(); ++j) {
                    // 判断该账号是否存在
                    if (p_datas[i].user.account.compare(l_tables[j].user.account) == 0) {
                        // 比较内容： 用户名
                        if (p_datas[i].user.name.compare(l_table.user.name) != 0) {
                            return COMPARED_FAILED;
                        }
                        // 比较内容： 用户生日
                        if (p_datas[i].user.birthday.compare(l_table.user.birthday) != 0) {
                            return COMPARED_FAILED;
                        }
                    }
                }

                if (j == l_tables.size()) {
                    return COMPARED_FAILED;
                }
            }
        } break;
        case SELECT_GROUP:
        {
            for (int i = 0; i < p_datas.size(); ++i) {
                l_query << "INSERT INTO group (account, name, manager_account, introduction) ";
                l_query << "VALUES (" << p_datas[i].group.account << ", " << p_datas[i].group.name << ", ";
                l_query << p_datas[i].group.manager_account << ", " << p_datas[i].group.introduction << ");";
                l_query.execute();
            }

            for (int i = 0; i < p_datas.size(); ++i) {
                if (p_mysql_test_instance.select_group_from_group_table(p_datas[i].group.account, l_table) == -1) {
                    return SELECT_FAILED;
                }
                // 比较内容： 群账号
                if (p_datas[i].group.account.compare(l_table.group.account) != 0) {
                    return COMPARED_FAILED;
                }
                // 比较内容： 群名
                if (p_datas[i].group.name.compare(l_table.group.name) != 0) {
                    return COMPARED_FAILED;
                }
                // 比较内容： 管理员账号
                if (p_datas[i].group.manager_account.compare(l_table.group.manager_account) != 0) {
                    return COMPARED_FAILED;
                }
                // 比较内容： 群介绍
                if (p_datas[i].group.introduction.compare(l_table.group.introduction) != 0) {
                    return COMPARED_FAILED;
                }
            }
        } break;
        case SELECT_GROUPS:
        {
            for (int i = 0; i < p_datas.size(); ++i) {
                l_query << "INSERT INTO group (account, name, manager_account, introduction) ";
                l_query << "VALUES (" << p_datas[i].group.account << ", " << p_datas[i].group.name << ", ";
                l_query << p_datas[i].group.manager_account << ", " << p_datas[i].group.introduction << ");";
                l_query.execute();
            }

            if (p_mysql_test_instance.select_all_groups_from_group_table(l_tables) == -1) {
                return SELECT_FAILED;
            }

            int i, j;
            for (i = 0; i < p_datas.size(); ++i) {
                for (j = 0; j < l_tables.size(); ++j) {
                    // 判断该账号是否存在
                    if (p_datas[i].group.account.compare(l_tables[j].group.account) == 0) {
                        // 比较内容： 群名
                        if (p_datas[i].group.name.compare(l_table.group.name) != 0) {
                            return COMPARED_FAILED;
                        }
                        // 比较内容： 管理员账号
                        if (p_datas[i].group.manager_account.compare(l_table.group.manager_account) != 0) {
                            return COMPARED_FAILED;
                        }
                        // 比较内容： 群介绍
                        if (p_datas[i].group.introduction.compare(l_table.group.introduction) != 0) {
                            return COMPARED_FAILED;
                        }
                    }
                }

                if (j == l_tables.size()) {
                    return COMPARED_FAILED;
                }
            }
        } break;
        case SELECT_USER_FRIENDS:
        {
            for (int i = 0; i < p_datas.size(); ++i) {
                l_query << "INSERT INTO user_friend (user_account, friend_account) ";
                l_query << "VALUES (" << p_datas[i].user_friend.user_account << ", " << p_datas[i].user_friend.friend_account << ");";
                l_query.execute();
            }

            if (p_mysql_test_instance.select_users_friends(p_datas[0].user_friend.user_account, l_tables) == -1) {
                return SELECT_FAILED;
            }

            int i, j;
            for (i = 0; i < p_datas.size(); ++i) {
                for (j = 0; j < l_tables.size(); ++j) {
                    // 这个测试只插入一个用户的好友， 因此用户账号应始终保持相同的
                    if (p_datas[i].user_friend.user_account.compare(l_tables[j].user_friend.user_account) != 0) {
                        return COMPARED_FAILED;
                    }
                    // 测试该好友是否成功保存
                    if (p_datas[i].user_friend.friend_account.compare(l_tables[j].user_friend.friend_account) == 0) {
                        break;
                    }
                }

                if (j == l_tables.size()) {
                    return COMPARED_FAILED;
                }
            }
        } break;
        case SELECT_GROUP_MEMBERS:
        {
            for (int i = 0; i < p_datas.size(); ++i) {
                l_query << "INSERT INTO group_member (group_account, member_account) ";
                l_query << "VALUES (" << p_datas[i].group_member.group_account << ", " << p_datas[i].group_member.member_account << ");";
                l_query.execute();
            }

            if (p_mysql_test_instance.select_groups_members(p_datas[0].group_member.group_account, l_tables) == -1) {
                return SELECT_FAILED;
            }

            int i, j;
            for (i = 0; i < p_datas.size(); ++i) {
                for (j = 0; j < l_tables.size(); ++j) {
                    // 这个测试只插入一个群组的好友， 因此群账号应始终保持相同的
                    if (p_datas[i].group_member.group_account.compare(l_tables[j].group_member.group_account) != 0) {
                        return COMPARED_FAILED;
                    }
                    // 测试该群成员是否存在
                    if (p_datas[i].group_member.member_account.compare(l_tables[j].group_member.member_account) == 0) {
                        break;
                    }
                }

                if (j == l_tables.size()) {
                    return COMPARED_FAILED;
                }
            }
        } break;
        case SELECT_USER_JOINED_GROUPS:
        {
            for (int i = 0; i < p_datas.size(); ++i) {
                l_query << "INSERT INTO user_joined_group (user_account, group_account) ";
                l_query << "VALUES (" << p_datas[i].user_joined_group.user_account << ", " << p_datas[i].user_joined_group.group_account << ");";
                l_query.execute();
            }

            if (p_mysql_test_instance.select_all_user_jonined_groups(p_datas[0].user_joined_group.user_account, l_tables) == -1) {
                return SELECT_FAILED;
            }

            int i, j;
            for (i = 0; i < p_datas.size(); ++i) {
                for (j = 0; j < l_tables.size(); ++j) {
                    // 这个测试只插入一个用户所加的群组， 因此用户账号应始终保持相同的
                    if (p_datas[i].user_joined_group.user_account.compare(l_tables[j].user_joined_group.user_account) != 0) {
                        return COMPARED_FAILED;
                    }
                    // 测试该群账号是否存在
                    if (p_datas[i].user_joined_group.group_account.compare(l_tables[j].user_joined_group.group_account) == 0) {
                        break;
                    }
                }

                if (j == l_tables.size()) {
                    return COMPARED_FAILED;
                }
            }
        } break;
        case SELECT_USER_MANAGED_GROUPS:
        {
            for (int i = 0; i < p_datas.size(); ++i) {
                l_query << "INSERT INTO user_managed_account (manager_account, group_account) ";
                l_query << "VALUES (" << p_datas[i].user_managed_group.manager_account << ", " << p_datas[i].user_managed_group.group_account << ");";
                l_query.execute();
            }

            if (p_mysql_test_instance.select_all_user_jonined_groups(p_datas[0].user_managed_group.manager_account, l_tables) == -1) {
                return SELECT_FAILED;
            }

            int i, j;
            for (i = 0; i < p_datas.size(); ++i) {
                for (j = 0; j < l_tables.size(); ++j) {
                    // 这个测试只插入一个用户所管理的群组， 因此管理员账号应始终保持相同的
                    if (p_datas[i].user_managed_group.manager_account.compare(l_tables[j].user_managed_group.manager_account) != 0) {
                        return COMPARED_FAILED;
                    }
                    // 测试该群账号是否存在
                    if (p_datas[i].user_managed_group.group_account.compare(l_tables[j].user_joined_group.group_account) == 0) {
                        break;
                    }
                }

                if (j == l_tables.size()) {
                    return COMPARED_FAILED;
                }
            }
        } break;
        default: 
            return UNKNOWN_OPTION;
    };

    return TEST_SUCCESSED;
}

uint8_t
MysqlTest_insert_row_to_table_test(MysqlTest& p_mysql_test_instance, struct database_table& p_table)
{
    switch (p_table.value_type)
    {
        case USER_TABLE:
        {
            // 待测试语句
            if (p_mysql_test_instance.insert_user_record_to_user_table(p_table) == -1) {
                return INSERT_FAILED;
            }
            // 获取数据
            auto t_mysql_connector = p_mysql_test_instance.get_mysqlpp_connector();
            mysqlpp::Query t_query = t_mysql_connector.query();
            t_query << "SELECT account, name, password, birthday FROM test.user WHERE account = \"" << p_table.user.account << "\";";
            mysqlpp::StoreQueryResult t_res = t_query.store();

            if (t_res.begin() == t_res.end()) {
                return CANT_FIND_DATA;
            }
            // 比较
            // 比较内容： 用户名
            if (p_table.user.account.compare(t_res[0]["account"].c_str()) != 0) {
                return COMPARED_FAILED;
            }
            // 比较内容： 账号
            if (p_table.user.name.compare(t_res[0]["name"].c_str()) != 0) {
                return COMPARED_FAILED;
            }
            // 比较内容： 密码
            if (p_table.user.password.compare(t_res[0]["password"].c_str()) != 0) {
                return COMPARED_FAILED;
            }
            // 比较内容： 生日
            if (p_table.user.birthday.compare(t_res[0]["birthday"].c_str()) != 0) {
                return COMPARED_FAILED;
            }
        } break;
        case USER_FRIEND_TABLE:
        {
            // 待测试语句
            if (p_mysql_test_instance.insert_user_friend_record_to_user_friend_table(p_table) == -1) {
                return INSERT_FAILED;
            }

            // 获取数据
            auto t_mysql_connector = p_mysql_test_instance.get_mysqlpp_connector();
            mysqlpp::Query t_query = t_mysql_connector.query();
            t_query << "SELECT user_account, friend_account FROM test.user_friend WHERE user_account = \"" << p_table.user_friend.user_account << "\";";
            mysqlpp::StoreQueryResult t_res = t_query.store();

            if (t_res.begin() == t_res.end()) {
                return CANT_FIND_DATA;
            }

            // 比较 
            // 比较内容： 用户账号
            if (p_table.user_friend.user_account.compare(t_res[0]["user_account"].c_str()) != 0) {
                return COMPARED_FAILED;
            }
            // 比较内容： 好友账号
            if (p_table.user_friend.friend_account.compare(t_res[0]["friend_account"].c_str()) != 0) {
                return COMPARED_FAILED;
            }
        } break;
        case GROUP_TABLE:
        {
            // 待测试语句
            if (p_mysql_test_instance.insert_group_record_to_group_table(p_table) == -1) {
                return INSERT_FAILED;
            }

            // 获取数据
            auto t_mysql_connector = p_mysql_test_instance.get_mysqlpp_connector();
            mysqlpp::Query t_query = t_mysql_connector.query();
            t_query << "SELECT account, name, manager_account, introduction FROM test.group WHERE account = \"" << p_table.group.account << "\";";
            mysqlpp::StoreQueryResult t_res = t_query.store();

            if (t_res.begin() == t_res.end()) {
                return CANT_FIND_DATA;
            }

            // 比较
            // 比较内容： 群账号
            if (p_table.group.account.compare(t_res[0]["account"].c_str()) == -1) {
                return COMPARED_FAILED;
            }
            // 比较内容: 群名称
            if (p_table.group.name.compare(t_res[0]["name"].c_str()) == -1) {
                return COMPARED_FAILED;
            }
            // 比较内容： 群管理员账号
            if (p_table.group.manager_account.compare(t_res[0]["manager_account"].c_str()) == -1) {
                return COMPARED_FAILED;
            }
            // 比较内容： 群介绍
            if (p_table.group.introduction.compare(t_res[0]["introduction"].c_str()) == -1) {
                return COMPARED_FAILED;
            }
        } break;
        case GROUP_MEMBER_TABLE:
        {
            if (p_mysql_test_instance.insert_group_member_record_to_group_member_table(p_table) == -1) {
                return INSERT_FAILED;
            }

            // 获取数据
            auto t_mysql_connector = p_mysql_test_instance.get_mysqlpp_connector();
            mysqlpp::Query t_query = t_mysql_connector.query();
            t_query << "SELECT group_account, member_account FROM test.group_member WHERE group_account = \"" << p_table.group_member.group_account << "\";";
            mysqlpp::StoreQueryResult t_res = t_query.store();

            if (t_res.begin() == t_res.end()) {
                return CANT_FIND_DATA;
            }

            // 比较
            // 比较内容： 群账号
            if (p_table.group_member.group_account.compare(t_res[0]["group_account"].c_str()) == -1) {
                return COMPARED_FAILED;
            }
            // 比较内容： 群成员账号
            if (p_table.group_member.member_account.compare(t_res[0]["member_account"].c_str()) == -1) {
                return COMPARED_FAILED;
            }
        } break;
        case USER_JOINED_GROUP_TABLE:
        {
            if (p_mysql_test_instance.insert_user_joined_group_record_to_user_joined_group_table(p_table) == -1) {
                return INSERT_FAILED;
            }

            // 获取数据
            auto t_mysql_connector = p_mysql_test_instance.get_mysqlpp_connector();
            mysqlpp::Query t_query = t_mysql_connector.query();
            t_query << "SELECT user_account, group_account FROM test.user_joined_group WHERE user_account = \"" << p_table.user_joined_group.user_account << "\";";
            mysqlpp::StoreQueryResult t_res = t_query.store();

            if (t_res.begin() == t_res.end()) {
                return CANT_FIND_DATA;
            }

            // 比较
            // 比较内容： 用户账号
            if (p_table.user_joined_group.user_account.compare(t_res[0]["user_account"].c_str()) == -1) {
                return COMPARED_FAILED;
            }
            // 比较内容： 群账号
            if (p_table.user_joined_group.group_account.compare(t_res[0]["group_account"].c_str()) == -1) {
                return COMPARED_FAILED;
            }
        } break;
        case USER_MANAGERED_GROUP_TABLE:
        {
            if (p_mysql_test_instance.insert_user_managered_group_record_to_user_managered_group_table(p_table) == -1) {
                return INSERT_FAILED;
            }

            // 获取数据
            auto t_mysql_connector = p_mysql_test_instance.get_mysqlpp_connector();
            mysqlpp::Query t_query = t_mysql_connector.query();
            t_query << "SELECT manager_account, group_account FROM test.user_managed_group WHERE manager_account = \"" << p_table.user_managed_group.manager_account << "\";";
            mysqlpp::StoreQueryResult t_res = t_query.store();

            if (t_res.begin() == t_res.end()) {
                return CANT_FIND_DATA;
            }

            // 比较
            // 比较内容： 管理员账号
            if (p_table.user_managed_group.manager_account.compare(t_res[0]["manager_account"].c_str()) == -1) {
                return COMPARED_FAILED;
            }
            // 比较内容： 群账号
            if (p_table.user_managed_group.group_account.compare(t_res[0]["group_account"].c_str()) == -1) {
                return COMPARED_FAILED;
            }
        } break;
        default:
            return UNKNOWN_OPTION;
            break;
    }
    return TEST_SUCCESSED;
}