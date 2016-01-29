<?php
	include("xmlrpc.inc");
	include("method.php");
	$client =new xmlrpc_client("/RPC2", $_SERVER["HTTP_HOST"], 8080);
	$sessionID = $_POST["sessionID"];
	$raw_params = $_POST["params"];
	$method = $_POST["method"];
	
	//$sessionID = "";
	//$raw_params = '{}';
	//$method = "GetSysInfo";

	$json_params = json_decode($raw_params,true);
	//var_dump($json_params);
	$xmlrpc_params = makeInputParams($method,$sessionID,$json_params);
	$f=new xmlrpcmsg($method, $xmlrpc_params);
	//$client->setDebug(2);
	$resp=&$client->send($f);
	if (!$resp) { print "IO error: ".$client->errstr; }
	if(!$resp->faultCode()){
		$value=$resp->value();
		$return_arr_value = php_xmlrpc_decode($value);
		print makeOutputParams($method,$return_arr_value);
	}
	else{
		print "An error occurred: ";
		print "Code: " . $resp->faultCode()." Reason: '" . $resp->faultString()."'";
	}
?>