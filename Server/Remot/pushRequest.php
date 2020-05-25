<?php

require  './Functions.php';

if (isset($_GET)) {

    $time = $_GET['time'];
    $temp = $_GET['temp'];
    $hum = $_GET['hum'];

    $table = "data";
    $datas = $GLOBALS['database']->insert($table, [
        "time" => $time,
        "temp" => $temp,
        "hum" => $hum,
    ]);
    echo "OK";

}

?>

