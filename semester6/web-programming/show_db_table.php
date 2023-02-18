<?php

include_once("fetch_all.php");

function show_db_table(mysqli_result $result, $tableStyle, 
ColumnInfo $updateColumn = null, ColumnInfo $deleteColumn = null) {

    echo "<table style='".$tableStyle."'>";

    //$rows = $result->fetch_all(MYSQLI_ASSOC); not supported on the server lmao (php 5.3.3)

    $rows = fetch_all($result);
    if (count($rows) == 0)
    {
        echo "<td>Table is empty</td>";
        echo "</table>";
        return;
    }

    $columnNames = array_keys($rows[0]);

    if (isset($updateColumn))
        $columnNames[] = $updateColumn->title;

    if (isset($deleteColumn))
        $columnNames[] = $deleteColumn->title;

    echoRow($columnNames, true);

    foreach ($rows as $row) {

        echo "<tr>";       

        echoRow($row, false);

        $id = $row[$columnNames[0]];

        if (isset($updateColumn))
            echo "<td><a href=".$updateColumn->linkToChangeScript."?id=".$id.">".
            $updateColumn->cellText."</a></td>";
        if (isset($deleteColumn))
            echo "<td><a href=".$deleteColumn->linkToChangeScript."?id=".$id.">".
            $deleteColumn->cellText."</a></td>";

        echo "</tr>";
    }

    echo "</table>";
}

class ColumnInfo {
    public $title; //no types because on server php 5.3.5 :(
    public $linkToChangeScript;
    public $cellText;

    public function __construct($title, $linkToChangeScript, $cellText) {
        $this->title = $title;
        $this->linkToChangeScript = $linkToChangeScript;
        $this->cellText = $cellText;
    }
    
}

function echoRow(array $row, $isHeaders) {
    foreach ($row as $data)
        echo $isHeaders ? "<th>".$data."</th>" : "<td>".$data."</td>";
}