	<table border="0" cellspacing="0" cellpadding="0"><tr>
	
		<!-- LEFT MENU START -->
		<td valign="top" bgcolor="#FFFFFF"><div id="leftpanel">
			
			<?php $base =& $GLOBALS['ESPCONFIG']['ME']; ?>

			<ul id="menutabs">
				<li class="lefthome"><a href="<?php echo("${base}?where=manage");     ?>"><?php echo(_('Home')); ?></a></li>

			   	<li class="leftresearch"><a href="<?php echo("${base}?where=newproject");     ?>"><?php echo(_('Create New Project')); ?></a></li>
				<li class="leftresearch"><a href="<?php echo("${base}?where=copyproject");    ?>"><?php echo(_('Copy Project')); ?></a></li>
		    	<li class="leftresearch"><a href="<?php echo("${base}?where=status");    ?>"><?php echo(_('Manage Projects')); ?></a></li>
				<li class="leftresearch"><a href="<?php echo("${base}?where=access");    ?>"><?php echo(_('Change Project Privacy')); ?></a></li>
				<li class="leftresearch"><a href="<?php echo("${base}?where=viewresults");    ?>"><?php echo(_('View Results')); ?></a></li>

			
				<?php if($GLOBALS['ESPCONFIG']['auth_design']) { ?>
			
					<?php if($_SESSION['acl']['superuser'] == 'Y' || count($_SESSION['acl']['puser']) > 0) { ?>
						<li class="leftuseradmin"><a href="<?php echo("${base}?where=respondents"); ?>"><?php echo(_('Manage Users')); ?></a></li>
					<?php }
										
					if($_SESSION['acl']['superuser'] == 'Y' || count($_SESSION['acl']['pgroup']) > 0) { ?>
						<li class="leftuseradmin"><a href="<?php echo("${base}?where=designers");   ?>"><?php echo(_('Manage Researchers')); ?></a></li>
						
						<?php if($_SESSION['acl']['superuser'] == 'Y') { ?>
							<li class="leftuseradmin"><a href="<?php echo("${base}?where=groups"); ?>"><?php echo(_('Manage Groups')); ?></a></li>
						<?php }
					} 
				} ?>
						
				<?php if($GLOBALS['ESPCONFIG']['auth_type'] != 'ldap') { ?>
					<li class="leftadmin"><a href="<?php echo("${base}?where=passwd");   ?>"><?php echo(_('Change Password')); ?></a></li>
				<?php } ?>
							
				<li class="leftadmin"><a href="<?php echo("${base}?where=guide");  ?>"><?php echo(_('Help')); ?></a></li>
										
				<?php if($GLOBALS['ESPCONFIG']['auth_design']) { ?>
					<!-- Logout -->
						<li class="leftadmin"><a href="<?php echo("${base}?where=logout");  ?>"><?php echo(_('Sign Out')); ?></a></li>
					<!-- End Logout -->
				<?php } ?>
				<br/>
				<br/>
			</ul>        
		
		</div></td>
		<!-- LEFT MENU END -->

		<!-- RIGHT SIDE TEXT BOX START -->
		<td valign="top" bgcolor="#FFFFFF"><div class="contents">
      		<form method="post" id="phpesp" action="<?php echo($GLOBALS['ESPCONFIG']['ME']); ?>">
	