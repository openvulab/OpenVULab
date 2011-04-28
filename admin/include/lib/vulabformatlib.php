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
// OpenVuLab Data Formatting Library
// - A YorkU Project
// Written by: Blake Edwards
// blake@electBlake.com

function format_projects($projects = array(),$view = 'table-basic',$option=null) {

	if (count($projects) <= 0) { return 'No Projects Supplied to Format!'; }
	
	switch($view) {
		
		case 'table-basic':
		default:
		
			$output = '<table cellspacing="0" cellpadding="4">';
			while(list($id,$pname,$pre, $post,$premsg,$postmsg, $url) = fetch_row($projects))
			{
        		$projects->MoveNext();
				if($bg != $ESPCONFIG['bgalt_color1'])
					$bg = $ESPCONFIG['bgalt_color1'];
				else
					$bg = $ESPCONFIG['bgalt_color2'];
			
			
			//Lets Prepare the Action Links
			$newuser_url = htmlentities($GLOBALS['ESPCONFIG']['ME'] ."?where=tab&newid=${id}")
			$edit_url = htmlentities($GLOBALS['ESPCONFIG']['ME'] ."?where=viewresults&project=${id}");
			$remove_url = htmlentities($GLOBALS['ESPCONFIG']['ME'] ."?where=rmproject&id=${id}");
			$results_url = htmlentities($GLOBALS['ESPCONFIG']['ME'] ."?where=viewresults&project=${id}");
			
			$output .= '<tr style="background-color:'.$bg.'">';
			
			
//	<!-- Alternating Colors are set in the phpESP.ini.php file -->
	
<td>
			<!--<a href="<?php echo(); ?>"><?php echo($pname); ?></a>-->
			<table style="background-color: <?php echo($bg); ?>;">
			<tr><td align="left" width="70%">
			<a href="<?php echo(); ?>"><?php echo($pname); ?></a>
			</td>
			<td>
<a href="<?php echo(htmlentities($GLOBALS['ESPCONFIG']['ME'] ."?where=testersproject&project=${id}")); ?>"><img src="../images/user.png" title="Manage Users"/></a>

			
			</td>
			<td>
			<a href="<?php echo(htmlentities($GLOBALS['ESPCONFIG']['ME'] ."?where=editproject&id=${id}")); ?>"><img src="../images/edit.png" title="Edit"/></a>
			</td>
			<td>
			<a href="<?php echo(htmlentities($GLOBALS['ESPCONFIG']['ME'] ."?where=rmproject&id=${id}")); ?>"><img src="../images/delete.png" title="Delete -- UNDER CONSTR."/></a>
			</td>
			<td>
<a href="<?php echo(htmlentities($GLOBALS['ESPCONFIG']['ME'] ."?where=viewresults&project=${id}")); ?>"><img src="../images/checkmark.png" title="View Results of <?php echo($pname); ?>" /></a>
				
			</td>
			</tr>
			</table>
		</td>
	</tr>
<?php
	} // end while
?>
</table>
		
		break;
	}
} // End format_projets()

?>