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

/* $Id: esphtml.results.inc,v 1.14 2007/07/09 12:58:10 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// <jflemer@alum.rpi.edu>

// void		mkrespercent(int[char*] counts, int total, bool showTotals);
// void		mkresrank(int[char*] counts, int total, bool showTotals);
// void		mkrescount(int[char*] counts, int total, bool showTotals);
// void		mkreslist(int[char*] counts, int total, bool showTotals);
// void		mkresavg(int[char*] counts, int total, bool showTotals);

/* {{{ proto void mkrespercent(array weights, int total, int precision, bool show_totals)
  Builds HTML showing PERCENTAGE results. */
function mkrespercent($counts,$total,$precision,$showTotals,$vids=nul) {
	$i=0;
	$bg='';
?>
<table width="90%" border="0">
<?php
	while(list($content,$num) = each($counts)) {
		if($num>0) { $percent = $num/$total*100.0; }
		else { $percent = 0; }
		if($percent > 100) { $percent = 100; }

		if($bg != $GLOBALS['ESPCONFIG']['bgalt_color1'])
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color1'];
		else
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color2'];
?>
	<tr style="background-color:<?php echo($bg); ?>;">
		<td><?php echo($content); ?></td>
		<td align="right">
<?php
		if($num) {
			echo("&nbsp;<img src=\"" .$GLOBALS['ESPCONFIG']['image_url'] ."hbar_l.gif\" height=\"9\" width=\"4\" alt=\"".$percent."\"/>");
			printf("<img src=\"" .$GLOBALS['ESPCONFIG']['image_url'] ."hbar.gif\" height=\"9\" width=\"%d\" alt=\"\"/>",$percent*2);
			echo("<img src=\"" .$GLOBALS['ESPCONFIG']['image_url'] ."hbar_r.gif\" height=\"9\" width=\"4\" alt=\"\"/>");
			printf("&nbsp;%.${precision}f%%",$percent);
		}
?></td>
		<td align="right">(<?php echo($num); ?>)</td>
	</tr>
<?php
		$i += $num;
	} // end while
	if($showTotals) {
		if($i>0) { $percent = $i/$total*100.0; }
		else { $percent = 0; }
		if($percent > 100) { $percent = 100; }

		if($bg != $GLOBALS['ESPCONFIG']['bgalt_color1'])
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color1'];
		else
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color2'];
?>
	<tr style="background-color:<?php echo($bg); ?>;">
		<td><b><?php echo(_('TOTAL')); ?></b></td>
		<td align="right"><b>&nbsp;<?php
			echo("<img src=\"" .$GLOBALS['ESPCONFIG']['image_url'] ."hbar_l.gif\" height=\"9\" width=\"4\" alt=\"".$percent."\"/>");
			printf("<img src=\"" .$GLOBALS['ESPCONFIG']['image_url'] ."hbar.gif\" height=\"9\" width=\"%d\" alt=\"\"/>",$percent*2);
			echo("<img src=\"" .$GLOBALS['ESPCONFIG']['image_url'] ."hbar_r.gif\" height=\"9\" width=\"4\" alt=\"\"/>");
			printf("&nbsp;%.${precision}f%%",$percent); ?></b></td>
		<td align="right"><b><?php print "$i ($total)"; ?></b></td>
	</tr>
<?php } ?>
</table>
<?php
}
/* }}} */


/* {{{ proto void mkresrank(array weights, int total, int precision, bool show_totals)
   Builds HTML showing RANK results. */
function mkresrank($counts,$total,$precision,$showTotals,$vids=null) {
	$bg='';
?>
<table border="0">
	<tr>
		<td align="right"><b><?php echo(_('Rank')); ?></b></td>
		<td>&nbsp;</td>
		<td>&nbsp;</td>
		<td>&nbsp;</td>
	</tr>
<?php
	arsort($counts);
	$i=0; $pt=0;
	while(list($content,$num) = each($counts)) {
		if($num)
			$p = $num/$total*100.0;
		else
			$p = 0;
		$pt += $p;

		if($bg != $GLOBALS['ESPCONFIG']['bgalt_color1'])
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color1'];
		else
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color2'];
?>
	<tr style="background-color:<?php echo($bg); ?>;">
		<td align="right"><b><?php echo(++$i); ?></b></td>
		<td><?php echo($content); ?></td>
		<td align="right" width="60"><?php if($p) printf("%.${precision}f%%",$p); ?></td>
		<td align="right" width="60">(<?php echo($num); ?>)</td>
	</tr>
<?php
	} // end while
	if($showTotals) {
		if($bg != $GLOBALS['ESPCONFIG']['bgalt_color1'])
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color1'];
		else
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color2'];
?>
	<tr bgcolor="<?php echo($bg); ?>">
		<td colspan="2" align="left"><b><?php echo(_('TOTAL')); ?></b></td>
		<td align="right"><b><?php printf("%.${precision}f%%",$pt); ?></b></td>
		<td align="right"><b><?php print "$i ($total)"; ?></b></td>
	</tr>
<?php } ?>
</table>
<?php
}
/* }}} */

/* {{{ proto void mkrescount(array weights, int total, int precision, bool show_totals)
   Builds HTML showing COUNT results. */
function mkrescount($counts,$total,$precision,$showTotals,$vids=null) {
	$i=0;
?>
<table width="90%" border="0">
<?php
    $bg = '';
	while(list($content,$num) = each($counts)) {
		if($bg != $GLOBALS['ESPCONFIG']['bgalt_color1'])
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color1'];
		else
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color2'];
?>
	<tr bgcolor="<?php echo($bg); ?>">
		<td><?php echo($content); ?></td>
		<td align="right" width="60"><?php echo($num); ?></td>
		<td align="right" width="60">(<?php if($num) printf("%.${precision}f",$num/$total*100.0); ?>%)</td>
	</tr>
<?php
		$i += $num;
	} // end while
	if($showTotals) {
		if($bg != $GLOBALS['ESPCONFIG']['bgalt_color1'])
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color1'];
		else
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color2'];
?>
	<tr bgcolor="<?php echo($bg); ?>">
		<td><b><?php echo(_('TOTAL')); ?></b></td>
		<td align="right"><b><?php print "$i ($total)"; ?></b></td>
		<td align="right"><b>(<?php if($i) printf("%.${precision}f",$i/$total*100.0); ?>%)</b></td>
	</tr>
<?php	} ?>
</table>
<?php
}
/* }}} */

/* {{{ proto void mkreslist(array weights, int total, int precision, bool show_totals)
	Builds HTML showing LIST results. */
function mkreslist($counts,$total,$precision,$showTotals,$vids=null) {
	if($total==0)	return;
	$bg='';
?>
<table width="90%" border="0" cellpadding="1">
	<tr><th align="left"><?php echo(_('#')); ?></th><th><?php echo(_('Response')); ?></th></tr>
<?php
	$responsenumber = '0';
	while(list($text,$num) = each($counts)) {
		$vidid = $vids[$responsenumber].'.avi';
		if($bg != $GLOBALS['ESPCONFIG']['bgalt_color1'])
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color1'];
		else
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color2'];
			if (count($vids) > 0) { $vid = "<td align='left'><!-- <a href='http://130.63.175.158/$vids[$responsenumber]/$vidid' target='_blank'>View Video</a> --></td>"; }
		echo("<tr bgcolor=\"$bg\"><th align=\"left\" valign=\"top\" width='10'>$num</th><td align='left' width='300'>$text</td>$vid</tr>\n");
		$responsenumber += 1;
	}
?>
</table>
<?php
}
/* }}} */

/* {{{ proto void mkresavg(array weights, int total, int precision, bool show_totals)
	Builds HTML showing AVG results. */
function mkresavg($counts,$total,$precision,$showTotals,$length,$vids=null) {
	if (!$length)
		$length = 5;
	$width = 200 / $length;
?>
<table cellspacing="0" cellpadding="0">
	<tr>
		<td></td>
		<td colspan="<?php echo($length+2); ?>"><?php echo(_('Average rank')); ?></td>
	</tr>
	<tr>
		<td></td>
		<?php
			for ($i = 0; $i < $length; )
				echo( "<td align=\"right\" width=\"$width\">". ++$i ."</td>\n");
		?>
		<td width="20"></td>
		<td></td>
	</tr>
<?php
    $bg = '';
	while(list($content,$avg) = each($counts)) {
		if($bg != $GLOBALS['ESPCONFIG']['bgalt_color1'])
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color1'];
		else
			$bg = $GLOBALS['ESPCONFIG']['bgalt_color2'];
?>
	<tr bgcolor="<?php echo($bg); ?>">
		<td><?php echo($content); ?>&nbsp;</td>
		<td colspan="<?php echo($length+1); ?>">
<?php
		if($avg) {
			echo('<img src="'. $GLOBALS['ESPCONFIG']['image_url'] .'hbar_l.gif" height="9" width="4">');
			if (($j = $avg * $width - 11) > 0)
				printf('<img src="'. $GLOBALS['ESPCONFIG']['image_url'] .'hbar.gif" height="9" width="%d">', $j);
			echo('<img src="'. $GLOBALS['ESPCONFIG']['image_url'] .'hbar_r.gif" height="9" width="4">');
		}
?>
		</td>
		<td width="60">(<?php printf("%.${precision}f",$avg); ?>)</td>
	</tr>
<?php
	} // end while
?>
</table>
<?php
}
/* }}} */

?>