<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?>
<?php

/* $Id: index.php,v 1.5 2005/08/01 16:12:52 greggmc Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

    if (isset($_SERVER))  $s =& $_SERVER;
    //else                  $s =& $HTTP_SERVER_VARS;

    if (isset($s['HTTPS']) && $s['HTTPS'] == 'on') {
        $proto = 'https';
        $port  = 443;
    } else {
        $proto = 'http';
        $port  = 80;
    }

    if (isset($s['SERVER_PORT']) && $s['SERVER_PORT'] != $port) {
        $port = ':' . $s['SERVER_PORT'];
    } else {
        $port = '';
    }

    $url = sprintf('%s://%s%s%s%s', $proto, $s['SERVER_NAME'], $port,
            dirname($s['SCRIPT_NAME']), '/manage.php');

    header("Location: $url");
?>