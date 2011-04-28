<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?><?php

/* $Id: todo.inc,v 1.5 2005/04/14 17:51:22 greggmc Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

?>
<?php echo("<a href=\"". $GLOBALS['ESPCONFIG']['ME'] ."?where=manage\">" . _('Go back to Management Interface - todo') . "</a>\n"); ?>
<?php if (file_exists($ESPCONFIG['include_path']."/../../TODO")) { ?>
<table><tr><td><pre>
<?php include($ESPCONFIG['include_path']."/../../TODO"); ?>
</pre></td></tr></table>
<?php
	} else {
		echo('<p>' . mkwarn(_('Todo list not found.')) . "</p>\n");
	}
?>
<?php echo("<a href=\"". $GLOBALS['ESPCONFIG']['ME'] ."?where=manage\">" . _('Go back to Management Interface - todo 2') . "</a>\n"); ?>
?>