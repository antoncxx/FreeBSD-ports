<?php

global $priv_list;

$priv_list['page-services-wallmon'] = array();
$priv_list['page-services-wallmon']['name'] = "WebCfg - Services: Wallmon";
$priv_list['page-services-wallmon']['descr'] = "Allow access to Wallmon package GUI";

$priv_list['page-services-wallmon']['match'] = array();
$priv_list['page-services-wallmon']['match'][] = "pkg_edit.php?xml=wallmon.xml";

