<?php
require  'Medoo.php';
// Using Medoo namespace
use Medoo\Medoo;

// $database = new Medoo([
//     // required
//     'database_type' => 'mysql',
//     'database_name' => 'test',
//     'server' => 'localhost',
//     'username' => 'root',
//     'password' => '',
//     'charset' => 'utf8mb4',
//     'collation' => 'utf8mb4_unicode_520_ci',
//     'logging' => true,
// ]);
$database = new Medoo([
    // required
    'database_type' => 'mysql',
    'database_name' => 'test',
    'server' => 'localhost',
    'username' => 'root',
    'password' => '1234567890',
    'charset' => 'utf8mb4',
    'collation' => 'utf8mb4_unicode_520_ci',
    'logging' => true,
]);


