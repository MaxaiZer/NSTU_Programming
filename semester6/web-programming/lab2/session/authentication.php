<?php

function authenticate(mysqli $conn, string $login, string $password) {

    session_start();

    $format = "select * from users where login = '%s'";
    $res = $conn->query(sprintf($format, $login), MYSQLI_USE_RESULT);

    $arr = $res->fetch_array();

    if (!isset($arr)) return false;

    $sault = $arr["sault"];
    $role = $arr["role"];

    $eq = md5($password.$sault) == $arr["password_hash"];

    if (!$eq) return false;

    $_SESSION["user_role"] = $role;
    return true;
}

function isUserWithLoginExists(mysqli $conn, string $login) {

    $format = "select * from users where login = '%s'";
    $res = $conn->query(sprintf($format, $login), MYSQLI_USE_RESULT);
    return count(fetch_all($res)) != 0;
}

function addUser(mysqli $conn, string $login, string $password, string $role) {

    if (isUserWithLoginExists($conn,$login))
        return false;

    $sault = substr(md5(mt_rand()), 0, 16);
    $password_hash = md5($password.$sault);

    $format = "insert into users (login, password_hash, sault, role)
    values ('%s', '%s', '%s', '%s');";

    $conn->query(sprintf($format, $login, $password_hash, $sault, $role), MYSQLI_USE_RESULT);
    return true;
}

function updateUser(mysqli $conn, $id, string $login, string $password, string $role) {

    $sault = substr(md5(mt_rand()), 0, 16);
    $password_hash = md5($password.$sault);

    $format = "update users set login = '%s', password_hash = '%s', 
    sault = '%s', role = '%s' where id = %d";

    try { $conn->query(sprintf($format, $login, $password_hash, $sault, $role, $id), MYSQLI_USE_RESULT); }
    catch (Exception $ex)
    { return false; }

    return true;
}