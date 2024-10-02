<?php

require_once('globals.inc');
require_once('config.inc');
require_once('service-utils.inc');
require_once('util.inc');
require_once('system.inc');

function wallmon_install() {
    safe_mkdir("/var/lock");
    # TODO:
    # unlink_if_exists("/usr/local/etc/rc.d/wallmon");
}

function wallmon_deinstall() {
    $logfiles = glob("/var/log/wallmon*");
    foreach($logfiles as $file) {
        if (is_file($file)) {
            unlink($file);
        }
    }

    #TODO: Delete all wallmon artifacts if they exist
    unlink_if_exists("/var/lock/wallmon.lock");
}

function wallmon_save() {
    global $g;

    $wallmon_config = array();
    
    foreach(config_get_path("installedpackages/wallmon/config/0", []) as $k => $v) {
        $wallmon_config[$k] = addslashes($v);
    }

    if ($wallmon_config['enable'] != "on") {
        if (is_service_running("wallmon")) {
            stop_service("wallmon");
        }

        unlink_if_exists("/usr/local/etc/rc.d/wallmon.sh");
        return;
    }

    if (empty($wallmon_config['hd_interval'])) {
        $wallmon_config['hd_interval'] = 60;
    }

    $pidfile = "{$g['varrun_path']}/wallmon.pid";
    write_rcfile(array(
        "file" => "wallmon.sh",
        "start" => "/usr/sbin/daemon -cP {$pidfile} /usr/local/bin/wallmon {$wallmon_config['serveraddr']}",
        "stop" => "/bin/kill `/bin/cat {$pidfile}`"
    ));

    if (is_service_running("wallmon")) {
        restart_service("wallmon");
    } else {
        start_service("wallmon");
    }
}

function wallmon_validate_input($post, &$input_errors) {
    if (!filter_var($post['serveraddr'], FILTER_VALIDATE_URL)) {
        $input_errors[] = gettext("'Server address' must be a valid IP address or URL.");
    }

    if (!empty($post['hb_interval']) && (
        !is_numeric($post['hb_interval']) ||
        (intval($post['hb_interval'] != $post['hb_interval'])) ||
        $post['hb_interval'] <= 0)) {
        
        $input_errors[] = gettext("Invalid heartbeat interval value");
    }
}

?>
