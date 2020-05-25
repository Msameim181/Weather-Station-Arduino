<?php

require  './Functions.php';

//Avalable Classes
$table = "data";
$data = $database->select($table, [
    "id",
    "time",
    "temp",
    "hum",

]);

$data_size = sizeof($data);
$last = $data[$data_size - 1];
echo json_encode(array('temp' => $last['temp'], 'hum' => $last['hum']));

?>

