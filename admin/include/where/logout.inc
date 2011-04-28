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

/* $Id: logout.inc,v 1.5 2007/12/10 12:15:55 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// <jflemer@alum.rpi.edu>
// <jflemer@acm.rpi.edu>

	manage_logout();
?>
<table cellspacing="0" cellpadding="4">
	<tr>
		<td><?php echo _('Logged out.'); ?><br>
			<?php echo("<a href=\"". $GLOBALS['ESPCONFIG']['ME'] ."?where=manage\">" . _('Log back in.') . "</a>\n"); ?>
		</td>
	</tr>
	<script type="text/javascript">
		window.location = "/admin/";
	</script>
</table>
&nbsp;
