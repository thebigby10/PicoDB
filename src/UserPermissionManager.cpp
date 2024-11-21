// #ifndef USER_PERMISSION_MANAGER_H
// #define USER_PERMISSION_MANAGER_H

// #include "ConfigManager.cpp"
// #include "String.cpp"
// #include "Vector.cpp"

// class UserPermissionManager {
// private:
//     ConfigManager configManager;

// public:
//     // Constructor that initializes the ConfigManager
//     UserPermissionManager(const String& configFilePath)
//         : configManager(configFilePath) {}

//     // Add a new user to the permissions section
//     void addUser(const String& username) {
//         String newUserEntry = username + String(" = \n");
//         configManager.appendConfig(newUserEntry, true); // Append to the config file
//     }

//     // Grant a user access to a table
//     void grantPermission(const String& username, const String& tableName) {
//         Vector<String> currentPermissions = getPermissions(username);
//         if (currentPermissions.contains(tableName)) {
//             std::cout << "User already has access to table " << tableName << std::endl;
//             return;
//         }
//         currentPermissions.push_back(tableName);
//         updatePermissions(username, currentPermissions);
//     }

//     // Revoke a user's access to a table
//     void revokePermission(const String& username, const String& tableName) {
//         Vector<String> currentPermissions = getPermissions(username);
//         Vector<String> updatedPermissions;
//         for (size_t i = 0; i < currentPermissions.get_size(); ++i) {
//             if (currentPermissions[i] != tableName) {
//                 updatedPermissions.push_back(currentPermissions[i]);
//             }
//         }
//         updatePermissions(username, updatedPermissions);
//     }

//     // Get the list of tables a user has access to
//     Vector<String> getPermissions(const String& username) {
//         String configData = configManager.getConfigData();
//         int start_pos = configData.findSubstring(username + " = ");
//         if (start_pos == -1) return Vector<String>(); // User not found
//         start_pos += (username + " = ").length();

//         int end_pos = start_pos;
//         while (end_pos < configData.length() && configData[end_pos] != '\n') {
//             ++end_pos;
//         }

//         String permissionsStr = configData.substr(start_pos, end_pos - start_pos).trim();
//         return splitPermissions(permissionsStr);
//     }

// private:
//     // Split a permission string into a vector of table names
//     Vector<String> splitPermissions(const String& permissionsStr) {
//         Vector<String> permissions;
//         size_t pos = 0;
//         String remaining = permissionsStr;

//         while ((pos = remaining.find(',')) != -1) {
//             permissions.push_back(remaining.substr(0, pos).trim());
//             remaining = remaining.substr(pos + 1);
//         }

//         if (remaining.length() > 0) {
//             permissions.push_back(remaining.trim());
//         }

//         return permissions;
//     }

//     // Update a user's permissions in the config file
//     void updatePermissions(const String& username, const Vector<String>& permissions) {
//         String permissionsStr;
//         for (size_t i = 0; i < permissions.get_size(); ++i) {
//             permissionsStr += permissions[i];
//             if (i != permissions.get_size() - 1) {
//                 permissionsStr += ", ";
//             }
//         }

//         String configData = configManager.getConfigData();
//         int start_pos = configData.findSubstring(username + " = ");
//         if (start_pos == -1) {
//             // User not found, add a new entry
//             addUser(username);
//             start_pos = configData.findSubstring(username + " = ");
//         }
//         start_pos += (username + " = ").length();

//         int end_pos = start_pos;
//         while (end_pos < configData.length() && configData[end_pos] != '\n') {
//             ++end_pos;
//         }

//         configData = configData.substr(0, start_pos) + permissionsStr + configData.substr(end_pos);
//         configManager.updateConfig(configData); // Write the updated config back to the file
//     }
// };

// #endif // USER_PERMISSION_MANAGER_H
