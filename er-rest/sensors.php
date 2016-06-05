<?php
  error_reporting(E_ERROR | E_WARNING | E_PARSE);

  function connect(){
    $conn = mysql_connect("localhost","root","user");

    if (!$conn) {
      error("Unable to connect to DB: " . mysql_error());
    }

    if (!mysql_select_db("parking")) {
      error("Unable to select parking: " . mysql_error());
    }
  }

  function exec_query($query){
    $result = mysql_query($query);

    if (!$result) {
      error("Could not successfully run query ($query) from DB: " . mysql_error());
    }

    return $result;
  }

  function error($message){
    header('X-PHP-Response-Code: 400', true, 400);
    echo json_encode( array('error' => $message) );
    exit;
  }

  function index($request){
    $query = "SELECT * FROM sensors";

    if ($id = $request[0]) {
      $query = $query . " WHERE  sensorID = '". $id . "'";

      if ($status = $_GET['status']) {
        $query = $query . " AND status = '". ($status ? 1 : 0) . "'";
      }
    } else {
      if ($status = $_GET['status']) {
        $query = $query . " WHERE  status = '". ($status ? 1 : 0) . "'";
      }
    }

    $result = exec_query($query);

    if (mysql_num_rows($result) == 0) {
      echo json_encode(array());
      exit;
    }

    $sensors = array();
    while ($row = mysql_fetch_assoc($result)) {
      $sensors[] = $row;
    }
    mysql_free_result($result);

    echo json_encode( $sensors );
  }

  function create($request){
    $sensorID = $_POST['sensorID'];
    $lat = $_POST['lat'];
    $lon = $_POST['lon'];
    $status = $_POST['status'];

    if (array_key_exists('sensorID', $_POST) && array_key_exists('lat', $_POST) && array_key_exists('lon', $_POST) && array_key_exists('status', $_POST)) {
      $query = "INSERT INTO sensors (sensorID,lat,lon,status) VALUES('". $_POST['sensorID'] ."','". $_POST['lat']. "','". $_POST['lon']. "','". $_POST['status'] ."')";
    } else {
      error('You have to provide: sensorID,lat,lon,status');
    }

    exec_query($query);

    $result = exec_query("SELECT * FROM sensors WHERE sensorID = '". $_POST['sensorID'] . "'");

    if (mysql_num_rows($result) == 0) {
      echo json_encode(array());
      exit;
    }

    $sensors = array();
    while ($row = mysql_fetch_assoc($result)) {
      $sensors[] = $row;
    }
    mysql_free_result($result);

    echo json_encode( $sensors );
  }

  function update($request){
    parse_str(file_get_contents("php://input"),$post_vars);

    $lat = $post_vars['lat'];
    $lon = $post_vars['lon'];
    $status = $post_vars['status'];

    if ($id = $request[0]) {
      $query = "UPDATE sensors SET ";
      if (isset($lat)) $set_query = "lat = '". $lat ."'";
      if (isset($lon)){
        if(isset($set_query)){
          $set_query = $set_query . ", lon = '". $lon ."'";
        } else {
          $set_query = "lon = '". $lon ."'";
        }
      }
      if (isset($status)){
        if(isset($set_query)){
          $set_query = $set_query . ", status = '". $status ."'";
        } else {
          $set_query = "status = '". $status ."'";
        }
      }

      if(isset($set_query)){
        $query = $query . $set_query;
      } else {
        error('You have to provide at least one field to update');
      }

      $query = $query . " WHERE sensorID = '". $id . "'";
    } else {
      error('You have to provide an ID');
    }

    exec_query($query);

    $result = exec_query("SELECT * FROM sensors WHERE sensorID = '". $id . "'");

    if (mysql_num_rows($result) == 0) {
      echo json_encode(array());
      exit;
    }

    $sensors = array();
    while ($row = mysql_fetch_assoc($result)) {
      $sensors[] = $row;
    }
    mysql_free_result($result);

    echo json_encode( $sensors );
  }

  function delete($request){
    if ($id = $request[0]) {
      $query = "DELETE FROM sensors WHERE sensorID = '". $id . "'";
    } else {
      error('You have to provide an ID');
    }

    exec_query($query);
  }

  header('Content-Type: application/json');
  connect();

  $method = $_SERVER['REQUEST_METHOD'];
  $request = explode("/", substr(@$_SERVER['PATH_INFO'], 1));

  switch ($method) {
    case 'PUT':
      update($request);
      break;
    case 'POST':
      create($request);
      break;
    case 'GET':
      index($request);
      break;
    case 'DELETE':
      delete($request);
      header('X-PHP-Response-Code: 204', true, 204);
      break;
    default:
      error("No Method");
      break;
  }
?>
