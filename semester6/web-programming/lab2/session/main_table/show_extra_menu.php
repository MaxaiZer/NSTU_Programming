<?php

session_start();

include_once "../user_info.php";
$user = getUserInfo($canChangeMainTable, $canChangeUsersTable);

if ($user->canChangeMainTable)
    showInsertForm();
if ($user->canChangeUsersTable)
    showLinkToUsersTable();

$format = "<a href='%s'><h1>%s</h1></a>";

if ($user->loggedIn)
    echo sprintf($format, "../exit.php", "Выйти");
else
    echo sprintf($format, "../login.php", "Вход");

function showInsertForm()
{
    echo 
    "
    <form action='insert_into_db.php'>
        <p>
            <button style='padding:10px 10px; width:85px'>Insert</button>
        </p>
    </form>
    ";
}

function showLinkToUsersTable()
{
    echo "<a href='../users_table/index.php'><h1>Пользователи</h1></a>";
}