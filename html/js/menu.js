// written by ricardo
// rewritten/enhanced by gnarf @ #jquery freenode.com
$(document).ready(function() {
	$("#menu").find("h2").each(function(i) {
		var img = $( '<img src="images/menu_less.gif" />' ),
			elem = $( this ),
			// this assumes that the UL is directly after the H2
			list = elem.next();

		elem.prepend( img )
			.css( "cursor", "pointer" )
			.toggle( function() {
				img.attr('src', 'images/menu_more.gif');
				list.slideToggle("slow");
			}, function() {
				img.attr('src', 'images/menu_less.gif');
				list.slideToggle("slow");
		});

	});
	// Links
	$("div#menu ul li a").hover(function( e ) {
		var speed = 200,
			padding = 10,
			mode = e.type === "mouseenter" ? "+=" : "-=";
		$(this).parent("li").animate({
			paddingLeft: mode+padding+'px'
		}, speed );
	});
});
