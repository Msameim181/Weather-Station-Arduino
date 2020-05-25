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

?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Station 11</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
    <style>
        #information{
            /* display: none; */
        }
        .simple-grid {
            margin: 0 auto
        }
        .simple-btn {
            background: #232323;
            color : #fff
        }
        .simple-btn:hover {
            color : #fff !important
        }
        .form-control:focus {
            color: #495057;
            background-color: #fff;
            border-color: #cecece;
            outline: 0;
            box-shadow: 0 0 0 0.2rem #d4d4d4
        }
        @media (min-width: 650px) {
            .simple-grid {
                width : 600px;
            }
        }
        @media (max-width: 650px) {
            .simple-grid {
                width: 90%;
            }
            #d-table {
                /* padding-left: 0px; */
                
            }
        }
    </style>
</head>
<body class="simple-grid">
    
    <div class="container-scroller">
        <div class="container-fluid page-body-wrapper">
            <div class="main-panel">
                <div class="content-wrapper">
                    
                    <div class="row border-bottom py-3">
                        <h4 class="card-title border-top border-bottom py-3 w-100 text-center">Temperature And Humidity Station</h4>
                        <small class="card-description">
                            <b class="d-block mb-2">Description</b>
                            <div>This page built by PHP for reprsent temperature and humidity that stored in DB.</div>
                            <div>Also it can show immediately last information without refreshing the page.</div>
                            <div>But you should refresh page for the list.</div>
                            <div>This project built with these equipment:</div>
                            <ul>
                                <li>DHT11</li>
                                <li>MicroSD reader</li>
                                <li>Wemos D1 WiFi board</li>
                            </ul>
                            ENJOY IT :)
                        </small>
                    </div>

                    <div class="row border-bottom py-3" id="information">
                        <div class="col-md-12 grid-margin stretch-card">
                            <div id="context-menu-simple">
                                <b>Last Data in DB :</b>
                                <div>
                                    <b class="d-block">
                                        <span>Temperature : </span>
                                        <span id="temperature">0</span>
                                        <span>&deg;C</span>
                                    </b>
                                    <b class="d-block">
                                        <span>Humidity : </span>
                                        <span id="humidity">0</span>
                                        <span>%</span>
                                    </b>
                                </div>
                            </div>
                        </div>
                    </div>

                    <div class="row mb-3 mt-3">
                        <div class="col-md-12 text-center" id="d-table">
                            <table class="table">
                                <thead>
                                    <tr>
                                        <th>Time</th>
                                        <th>Temp</th>
                                        <th>Humidity</th>
                                    </tr>
                                </thead>
                                <tbody>
                                    <?php for ($i = (sizeof($data) - 1); $i >= 0; $i--) : ?>
                                    <tr>
                                        <td scope="row"><?php echo $data[$i]['time']; ?></td>
                                        <td><?php echo $data[$i]['temp']; ?></td>
                                        <td><?php echo $data[$i]['hum']; ?></td>
                                    </tr>
                                    <?php endfor; ?>
                                </tbody>
                            </table>
                        </div>
                    </div>

                </div>
            </div>
        </div>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <script>
        (function ($) {

            var interval = 2000;  // 1000 = 1 second, 3000 = 3 seconds
            function doAjax() {
                $.ajax({
                        type: 'GET',
                        url: 'returnLast.php',
                        data: $(this).serialize(),
                        dataType: 'json',
                        success: function (data) {
                            document.getElementById('temperature').innerHTML = data['temp'];
                            document.getElementById('humidity').innerHTML = data['hum'];
                        },
                        complete: function (data) {
                                // Schedule the next
                                setTimeout(doAjax, interval);
                        }
                });
            }
            setTimeout(doAjax, interval);
        })(jQuery);

        
    </script>
</body>
</html>