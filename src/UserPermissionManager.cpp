#ifndef USER_PERMISSION_MANAGER_H
#define USER_PERMISSION_MANAGER_H

#include "Database.cpp"
#include "String.cpp"
#include "Vector.cpp"

class UserPermissionManager {
private:
    Database& db;

public:
    // Constructor that initializes the ConfigManager
    UserPermissionManager(Database& db)
        : db(db) {}

    void addUser(const String& username, const String& tableName) {
        if (!db.isAdmin()) {
            std::cout << "You are not the admin. Only the admin can modify access permissions." << std::endl;
            return;
        }

        if (userExists(username)) {
            std::cout << "User already exists, use grantPermission to grant the user specific permission." << std::endl;
            return;
        } else {
            // Add new user with permissions
            Vector<String> user;
            Vector<String> permission;
            user.push_back(username);
            permission.push_back(tableName);

            // Work directly on the reference to allUserPermissionsInfo
            db.get_allUserPermissionsInfo().push_back(user);
            db.get_allUserPermissionsInfo().push_back(permission);
        }
    }


    // Grant a user access to a table
    void grantPermission(const String& username, const String& tableName) {
        if (!db.isAdmin()) {
            std::cout<< "You are not the admin. Only the admin can modify access permissions." << std::endl;
            return;
        }

        if (userExists(username)) {
            if (!userPermissionExists(username, tableName)){
                // update existing user permissions
                Vector<Vector<String>>& allUserPermissionsInfo = db.get_allUserPermissionsInfo();

                int size = allUserPermissionsInfo.get_size();
                for (int i=0; i<size; i+=2) {
                    if (username == allUserPermissionsInfo[i][0]) { 
                        // we're taking [i][0] and i+=2 cause every 2nd vector in allUserPermissionInfo contains the table name, need to use constants here later
                        allUserPermissionsInfo[i+1].push_back(tableName);
                        return;
                    }
                }
            } else {
                std::cout << "User already has access to table : " << tableName << std::endl; 
            }
        } else {
            std::cout << "User doesn't exist. Please, add new user or search for a different one." << std::endl;
        }
    }

    // Revoke a user's access to a table
    void revokePermission(const String& username, const String& tableName) {
        if (!db.isAdmin()) {
            std::cout<< "You are not the admin. Only the admin can modify access permissions." << std::endl;
            return;
        }

        if (userExists(username)) {
            if (userPermissionExists(username, tableName)){
                // update existing user permissions by removing the tablename
                Vector<Vector<String>>& allUserPermissionsInfo = db.get_allUserPermissionsInfo();

                int size = allUserPermissionsInfo.get_size();
                for (int i=0; i<size; i+=2) {
                    if (username == allUserPermissionsInfo[i][0]) { 
                        // we're taking [i][0] and i+=2 cause every 2nd vector in allUserPermissionInfo contains the table name, need to use constants here later
                        int sizeOfPermission = allUserPermissionsInfo[i+1].get_size();
                        for (int j=0; j<sizeOfPermission; j++) {
                            if (allUserPermissionsInfo[i+1][j] == tableName) {
                                allUserPermissionsInfo[i+1].erase(j);
                                return;
                            }
                        }
                    }
                }
            } else {
                std::cout << "User doesn't have access to table : " << tableName << std::endl; 
            }
        } else {
            std::cout << "User doesn't exist. Please, add new user or search for a different one." << std::endl;
        }
    }

private:
    bool userExists(String username) {
        Vector<Vector<String>> allUserPermissionsInfo;
        allUserPermissionsInfo = this->db.get_allUserPermissionsInfo();

        int size = allUserPermissionsInfo.get_size();
        for (int i=0; i<size; i+=2) {
            if (username == allUserPermissionsInfo[i][0]) { 
                // we're taking [i][0] and i+=2 cause every 2nd vector in allUserPermissionInfo contains the table name, need to use constants here later
                return true;
            }
        }
        return false;
    }

    bool userPermissionExists(String username, String inputPermission) {
        Vector<Vector<String>> allUserPermissionsInfo;
        allUserPermissionsInfo = this->db.get_allUserPermissionsInfo();

        int size = allUserPermissionsInfo.get_size();
        for (int i=0; i<size; i+=2) {
            if (username == allUserPermissionsInfo[i][0]) { 
                // we're taking [i][0] and i+=2 cause every 2nd vector in allUserPermissionInfo contains the table name, need to use constants here later
                Vector<String> permissions;
                permissions = allUserPermissionsInfo[i+1];
                int sizeOfPermissions = permissions.get_size();
                for(int j=0; j<sizeOfPermissions; j++) {
                    if (inputPermission == permissions[j]) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

#endif // USER_PERMISSION_MANAGER_H
