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

/* $Id: passwd.inc,v 1.7 2005/08/01 16:12:55 greggmc Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// <jflemer@alum.rpi.edu>
// <jflemer@acm.rpi.edu>

	/* ACL: everyone is allowed to change her own password */
?>
<h2><?php echo(_('Change Password')); ?></h2>
<?php
	if(isset($_POST['newpass1']) &&
		$_POST['newpass1'] == $_POST['newpass2'] &&
		!empty($_POST['newpass1'])) {
		if(auth_change_manager_passwd(
				$_SESSION['acl']['username'],
				_addslashes($_POST['oldpass']),
				_addslashes($_POST['newpass1']))) {
			echo(_('Your password has been successfully changed.') ."<br>\n");
			echo("<a href=\"". $GLOBALS['ESPCONFIG']['ME'] ."?where=manage\">" . _('Go back to Management Interface - passwd 1') . "</a>\n");
			return;
		} else {
			echo(mkerror(_('Password not set, check your old password.')));
		}
	} else if(isset($_POST['newpass1'])) {
		echo(mkerror(_('New passwords do not match or are blank.')));
	}
?>
<input type="hidden" name="where" value="passwd" />
<table cellspacing="0" cellpadding="4">
<tr>
	<th class="right">
	<?php echo(_('Username')); ?></th>
	<td class="left">
	<?php echo('<tt>'. $_SESSION['acl']['username'] .'</tt>'); ?></td>
</tr><tr>
	<th class="right">
	<?php echo(_('Old Password')); ?></th>
	<td class="left">
	<?php echo(mkpass('oldpass')); ?></td>
</tr><tr>
	<th class="right">
	<?php echo(_('New Password')); ?></th>
	<td class="left">
	<?php echo(mkpass('newpass1')); ?></td>
</tr><tr>
	<th class="right">
	<?php echo(_('Confirm New Password')); ?></th>
	<td class="left">
	<?php echo(mkpass('newpass2')); ?></td>
</tr><tr>
	<th colspan="2" class="center">
	<input type="submit" value="<?php echo(_('Change Password')); ?>" />
	</th>
</tr>
</table>
<?php echo("<a href=\"". $GLOBALS['ESPCONFIG']['ME'] ."?where=manage\">" . _('Go back to Management Interface - passwd 2') . "</a>\n"); ?>