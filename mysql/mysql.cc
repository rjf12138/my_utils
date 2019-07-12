#include "mysql.h"

 std::ostream& 
 operator<<(std::ostream& p_os, const database_table& p_table)
 {
    switch (p_table.value_type) {
        case USER_TABLE:
            p_os << "user_account: " << p_table.user.account << std::endl;
            p_os << "user_name: " << p_table.user.name << std::endl;
            p_os << "user_password: " << p_table.user.password << std::endl;
            p_os << "user_signature: " << p_table.user.signature << std::endl;
            p_os << "user_mail: " << p_table.user.mail << std::endl;
            p_os << "user_birthday: " << p_table.user.birthday << std::endl;
            break;
        case GROUP_TABLE:
            p_os << "group_account: " << p_table.group.account << std::endl;
            p_os << "group_name: " << p_table.group.name << std::endl;
            p_os << "manager_account: " << p_table.group.manager_account << std::endl;
            p_os << "introduction: " << p_table.group.introduction << std::endl;
            break;
        case USER_FRIEND_TABLE:
            p_os << "user_account: " << p_table.user_friend.user_account << std::endl;
            p_os << "friend_account: " << p_table.user_friend.friend_account << std::endl;
            break;
        case GROUP_MEMBER_TABLE:
            p_os << "group_account: " << p_table.group_member.group_account << std::endl;
            p_os << "group_member_account: " << p_table.group_member.member_account << std::endl;
            break;
        case USER_JOINED_GROUP_TABLE:
            p_os << "user_account: " << p_table.user_joined_group.user_account << std::endl;
            p_os << "joined_group_account:" << p_table.user_joined_group.group_account << std::endl;
            break;
        case USER_MANAGERED_GROUP_TABLE:
            p_os << "manager_account: " << p_table.user_managed_group.manager_account << std::endl;
            p_os << "group_account: " << p_table.user_managed_group.group_account << std::endl;
            break;
        default:
            p_os << "Unknown value" << std::endl;
            break;
    }
    return p_os;
 }


MysqlTest::MysqlTest(const std::string& p_database_name, const std::string& p_database_server_ip, 
                            const std::string& p_user_account, const std::string& p_user_password)
{
    d_database_connector.connect(p_database_name.c_str(), p_database_server_ip.c_str(), p_user_account.c_str(), p_user_password.c_str());
}

bool 
MysqlTest::is_user_exists(const std::string p_user_account)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT account FROM user WHERE account = " << p_user_account << ");";
    mysqlpp::StoreQueryResult t_res = l_query.store();

    if (t_res.begin() == t_res.end()) {
        return false;
    }

    return true;
}
bool 
MysqlTest::is_user_friend_exists(const std::string p_user_account, const std::string p_friend_account)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT " << p_friend_account << " FROM user_friend WHERE user_account = " << p_user_account << ");";
    mysqlpp::StoreQueryResult t_res = l_query.store();

    if (t_res.begin() == t_res.end()) {
        return false;
    }

    return true;
}
bool 
MysqlTest::is_group_exists(const std::string p_group_account)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT account FROM group WHERE account = " << p_group_account << ");";
    mysqlpp::StoreQueryResult t_res = l_query.store();

    if (t_res.begin() == t_res.end()) {
        return false;
    }

    return true;
}
bool 
MysqlTest::is_group_member_exists(const std::string p_group_account, const std::string p_member_account)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT " << p_member_account << " FROM group_member WHERE group_account = " << p_group_account << ");";
    mysqlpp::StoreQueryResult t_res = l_query.store();

    if (t_res.begin() == t_res.end()) {
        return false;
    }

    return true;
}
bool 
MysqlTest::check_user_password(const std::string p_user_account, const std::string p_password)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT password FROM user WHERE account = " << p_user_account << ");";
    mysqlpp::StoreQueryResult t_res = l_query.store();

    if (t_res.begin() == t_res.end()) {
        return false;
    }

    if (t_res[0]["password"].compare(p_password) != 0) {
        return false;
    }

    return true;
}


int 
MysqlTest::insert_user_record_to_user_table(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query(); 
    l_query << "INSERT INTO user (account, name, password, birthday) ";
    l_query << "VALUES (\"" << p_table.user.account << "\", \"" << p_table.user.name << "\", \"" << p_table.user.password << "\", \"";
    l_query << p_table.user.birthday << "\");";
    l_query.execute();

    return 0;
}

int 
MysqlTest::insert_user_friend_record_to_user_friend_table(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query(); 
    l_query << "INSERT INTO user_friend (user_account, friend_account) ";
    l_query << "VALUES (\"" << p_table.user_friend.user_account << "\", \"" << p_table.user_friend.friend_account << "\");";
    l_query.execute();

    return 0;
}
int 
MysqlTest::insert_user_joined_group_record_to_user_joined_group_table(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query(); 
    l_query << "INSERT INTO user_joined_group (user_account, group_account) ";
    l_query << "VALUES (\"" << p_table.user_joined_group.user_account << "\", \"" << p_table.user_joined_group.group_account << "\");";
    l_query.execute();

    return 0;
}
int 
MysqlTest::insert_group_record_to_group_table(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query(); 
    l_query << "INSERT INTO test.group (account, name, manager_account, introduction) ";
    l_query << "VALUES (\"" << p_table.group.account << "\", \"" << p_table.group.name << "\", \"" << p_table.group.manager_account << "\", \"";
    l_query << p_table.group.introduction << "\");";
    l_query.execute();

    return 0;
}
int 
MysqlTest::insert_group_member_record_to_group_member_table(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query(); 
    l_query << "INSERT INTO group_member (group_account, member_account) ";
    l_query << "VALUES (\"" << p_table.group_member.group_account << "\", \"" << p_table.group_member.member_account << "\");";
    l_query.execute();

    return 0;
}
int 
MysqlTest::insert_user_managered_group_record_to_user_managered_group_table(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query(); 
    l_query << "INSERT INTO user_managed_group (manager_account, group_account) ";
    l_query << "VALUES (\"" << p_table.user_managed_group.manager_account << "\", \"" << p_table.user_managed_group.group_account << "\");";
    l_query.execute();

    return 0;
}


int 
MysqlTest::select_user_from_user_table(const std::string user_account, struct database_table& p_user_table)
{
    mysqlpp::Query l_query = d_database_connector.query(); 
    l_query << "SELECT * FROM test.user WHERE account = \"" << user_account << "\";";
    mysqlpp::StoreQueryResult l_user_info = l_query.store();

    if (l_user_info.begin() == l_user_info.end()) {     // 返回结果是否为空
        return -1;
    }

    p_user_table.value_type = USER_TABLE;
    p_user_table.user.account = l_user_info[0]["account"].c_str();
    p_user_table.user.name = l_user_info[0]["name"].c_str();
    p_user_table.user.signature = l_user_info[0]["signature"].c_str();
    p_user_table.user.mail = l_user_info[0]["mail"].c_str();
    p_user_table.user.birthday = l_user_info[0]["birthday"].c_str();

    return 0;
}

int 
MysqlTest::select_all_users_from_user_table(std::vector<struct database_table>& p_users)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT * FROM test.user;";
    mysqlpp::StoreQueryResult l_user_infos = l_query.store();

    if (l_user_infos.begin() == l_user_infos.end()) {
        return -1;
    }

    struct database_table l_tmp_user;
    p_users.clear();
    for (int i = 0; i < l_user_infos.size(); ++i) {
        l_tmp_user.value_type = USER_TABLE;
        l_tmp_user.user.account = l_user_infos[i]["account"].c_str();
        l_tmp_user.user.name = l_user_infos[i]["name"].c_str();
        l_tmp_user.user.signature = l_user_infos[i]["signature"].c_str();
        l_tmp_user.user.mail = l_user_infos[i]["mail"].c_str();
        l_tmp_user.user.birthday = l_user_infos[i]["birthday"].c_str();

        p_users.push_back(l_tmp_user);
    }

    return 0;
}

int 
MysqlTest::select_group_from_group_table(const std::string group_account, struct database_table& p_group_table)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT * FROM test.group WHERE account = \"" << group_account << "\";";
    mysqlpp::StoreQueryResult l_group_info = l_query.store();

    if (l_group_info.begin() == l_group_info.end()) {
        return -1;
    }

    p_group_table.value_type = GROUP_TABLE;
    p_group_table.group.account = l_group_info[0]["account"].c_str();
    p_group_table.group.name = l_group_info[0]["name"].c_str();
    p_group_table.group.manager_account = l_group_info[0]["manager_account"].c_str();
    p_group_table.group.introduction = l_group_info[0]["introduction"].c_str();
    
    return 0;
}
int 
MysqlTest::select_all_groups_from_group_table(std::vector<struct database_table>& p_groups)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT * FROM test.group;";
    mysqlpp::StoreQueryResult l_group_infos = l_query.store();

    if (l_group_infos.begin() == l_group_infos.end()) {
        return -1;
    }

    struct database_table l_tmp_group;
    p_groups.clear();
    for (int i = 0; i < l_group_infos.size(); ++i) {
        l_tmp_group.value_type = GROUP_TABLE;
        l_tmp_group.group.account = l_group_infos[i]["account"].c_str();
        l_tmp_group.group.name = l_group_infos[i]["name"].c_str();
        l_tmp_group.group.manager_account = l_group_infos[i]["manager_account"].c_str();
        l_tmp_group.group.introduction = l_group_infos[i]["introduction"].c_str();

        p_groups.push_back(l_tmp_group);
    }

    return 0;
}
int 
MysqlTest::select_users_friends(const std::string p_user_account, std::vector<struct database_table>& p_friends)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT * FROM test.user_friend WHERE user_account = \"" << p_user_account << "\";";
    mysqlpp::StoreQueryResult l_friend_account = l_query.store();

    if (l_friend_account.begin() == l_friend_account.end()) {
        return -1;
    }

    struct database_table l_tmp_friend;
    p_friends.clear();
    for (int i = 0; i < l_friend_account.size(); ++i) {
        l_tmp_friend.value_type = USER_FRIEND_TABLE;
        l_tmp_friend.user_friend.user_account = l_friend_account[i]["user_account"].c_str();
        l_tmp_friend.user_friend.friend_account = l_friend_account[i]["friend_account"].c_str();

        p_friends.push_back(l_tmp_friend);
    }

    return 0;
}
int 
MysqlTest::select_groups_members(const std::string p_group_account, std::vector<struct database_table>& p_members)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT * FROM test.group_member WHERE group_account = \"" << p_group_account << "\";";
    mysqlpp::StoreQueryResult l_group_members = l_query.store();

    if (l_group_members.begin() == l_group_members.end()) {
        return -1;
    }

    struct database_table l_group_member;
    p_members.clear();
    for (int i = 0; i < l_group_members.size(); ++i) {
        l_group_member.value_type = GROUP_MEMBER_TABLE;
        l_group_member.group_member.group_account = l_group_members[i]["group_account"].c_str();
        l_group_member.group_member.member_account = l_group_members[i]["member_account"].c_str();

        p_members.push_back(l_group_member);
    }

    return 0;
}
int 
MysqlTest::select_all_user_managered_groups(const std::string p_manager_account, std::vector<struct database_table>& p_groups)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT * FROM test.user_managed_group WHERE manager_account = \"" << p_manager_account << "\";";
    mysqlpp::StoreQueryResult l_groups = l_query.store();

    if (l_groups.begin() == l_groups.end()) {
        return -1;
    }

    struct database_table l_managed_group;
    p_groups.clear();
    for (int i = 0; i < l_groups.size(); ++i) {
        l_managed_group.value_type = USER_MANAGERED_GROUP_TABLE;
        l_managed_group.user_managed_group.manager_account = l_groups[i]["manager_account"].c_str();
        l_managed_group.user_managed_group.group_account = l_groups[i]["group_account"].c_str();

        p_groups.push_back(l_managed_group);
    }

    return 0;
}

int 
MysqlTest::select_all_user_jonined_groups(const std::string p_user_account, std::vector<struct database_table>& p_groups)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "SELECT * FROM test.user_joined_group WHERE user_account = \"" << p_user_account << "\";";
    mysqlpp::StoreQueryResult l_groups = l_query.store();

    if (l_groups.begin() == l_groups.end()) {
        return -1;
    }

    struct database_table l_joined_group;
    p_groups.clear();
    for (int i = 0; i < l_groups.size(); ++i) {
        l_joined_group.value_type = USER_JOINED_GROUP_TABLE;
        l_joined_group.user_joined_group.user_account = l_groups[i]["user_account"].c_str();
        l_joined_group.user_joined_group.group_account = l_groups[i]["group_account"].c_str();

        p_groups.push_back(l_joined_group);
    }

    return 0;
}

int 
MysqlTest::update_user_name(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query(); 
    l_query << "UPDATE user SET name = " << p_table.user.name << " WHERE account = " << p_table.user.account << ";";
    l_query.execute();

    return 0;
}
int 
MysqlTest::update_user_password(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "UPDATE user SET password = " << p_table.user.password << " WHERE account = " << p_table.user.account << ";";
    l_query.execute();

    return 0;
}

int 
MysqlTest::update_user_mail(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "UPDATE user SET mail = " << p_table.user.mail << " WHERE account = " << p_table.user.account << ";";
    l_query.execute();

    return 0;
}
int 
MysqlTest::update_user_birthday(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "UPDATE user SET birthday = " << p_table.user.birthday << " WHERE account = " << p_table.user.account << ";";
    l_query.execute();

    return 0;
}
int 
MysqlTest::update_user_signature(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "UPDATE user SET signature = " << p_table.user.signature << " WHERE account = " << p_table.user.account << ";";
    l_query.execute();

    return 0;
}

int 
MysqlTest::update_group_manager(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "UPDATE group SET manger_account = " << p_table.group.manager_account << " WHERE account = " << p_table.group.account << ";";
    l_query.execute();

    return 0;
}
int 
MysqlTest::update_group_name(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "UPDATE group SET name = " << p_table.group.name << " WHERE account = " << p_table.group.account << ";";
    l_query.execute();

    return 0;
}

int 
MysqlTest::update_group_introduction(struct database_table& p_table)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "UPDATE group SET intruduction = " << p_table.group.introduction << " WHERE account = " << p_table.group.account << ";";
    l_query.execute();

    return 0;
}

int 
MysqlTest::delete_user_from_user_table(const std::string p_user_account)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "DELETE FROM user WHERE account = " << p_user_account << ";";
    l_query.execute();

    return 0;
}

int 
MysqlTest::delete_friend_from_user_friend_table(const std::string p_user_account, const std::string p_friend_account)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "DELETE FROM user_friend WHERE user_account = " << p_user_account << " AND friend_account = " << p_friend_account << ";";
    l_query.execute();

    return 0;
}
int 
MysqlTest::delete_member_from_group_member_table(const std::string p_group_account, const std::string p_member_account)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "DELETE FROM group_member WHERE group_account = " << p_group_account << " AND member_account = " << p_member_account << ";";
    l_query.execute();

    return 0;
}
int 
MysqlTest::delete_group_from_group_table(const std::string p_group_account)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "DELETE FROM group WHERE group_account = " << p_group_account << ";";
    l_query.execute();

    return 0;
}
int 
MysqlTest::delete_group_from_user_managed_group_table(const std::string p_manager_account, const std::string p_group_account)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "DELETE FROM user_managed_group WHERE manager_account = " << p_manager_account << " AND group_account = " << p_group_account << ";";
    l_query.execute();

    return 0;
}
int 
MysqlTest::delete_group_from_user_joined_group_table(const std::string p_user_account, const std::string p_group_account)
{
    mysqlpp::Query l_query = d_database_connector.query();
    l_query << "DELETE FROM user_joined_group WHERE manager_account = " << p_user_account << " AND group_account = " << p_group_account << ";";
    l_query.execute();

    return 0;
}

MysqlTest::~MysqlTest()
{
    d_database_connector.disconnect();
}