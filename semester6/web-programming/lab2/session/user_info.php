<?php

function getUserInfo()
{
    session_start();
    $canChangeMainTable = $canChangeUsersTable = false;

    $whoCanChangeMainTable = array("moderator", "admin");
    $whoCanChangeUsersTable = array("admin");

    $loggedIn = isset($_SESSION["user_role"]);

    if (!$loggedIn)
        return new UserInfo($loggedIn, $canChangeMainTable, $canChangeUsersTable);

    if (in_array($_SESSION["user_role"], $whoCanChangeMainTable))
        $canChangeMainTable = true;
    if (in_array($_SESSION["user_role"], $whoCanChangeUsersTable))
        $canChangeUsersTable = true;

    return new UserInfo($loggedIn, $canChangeMainTable, $canChangeUsersTable);
}

class UserInfo {

    public $loggedIn;
    public $canChangeMainTable;
    public $canChangeUsersTable;

    public function __construct($loggedIn, $canChangeMainTable, $canChangeUsersTable) {
        $this->loggedIn = $loggedIn;
        $this->canChangeMainTable = $canChangeMainTable;
        $this->canChangeUsersTable = $canChangeUsersTable;
    }
}