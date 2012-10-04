(function($){

$(document).ready(function() {	


	/* Get the juicy GMAP Data */
	var title = Drupal.settings.content_gmap.title;
	var type = Drupal.settings.content_gmap.type;
	var zoom = parseInt(Drupal.settings.content_gmap.zoom, 10);
	var lat = Drupal.settings.content_gmap.lat;
	var lng = Drupal.settings.content_gmap.lng;
	var showMarker = Drupal.settings.content_gmap.marker;
	var mlat = Drupal.settings.content_gmap.mlat;
	var mlng = Drupal.settings.content_gmap.mlng;
	
	/* Not used for now
	var info =  Drupal.settings.content_gmap.info;
	*/
	var admin = Drupal.settings.content_gmap.admin;
	var path = Drupal.settings.content_gmap.path;
	var op = Drupal.settings.content_gmap.op;
	
	var maptype = google.maps.MapTypeId[type];
	
    var latlng = new google.maps.LatLng(lat, lng);
    var mlatlng = new google.maps.LatLng(mlat, mlng);

    var marker;
    var myOptions = {
      zoom: zoom,
      center: latlng,
      mapTypeId: maptype,
      scrollwheel: false
    };
   
   var map = new google.maps.Map(document.getElementById("content-gmap"),
        myOptions);
   
   var image = new google.maps.MarkerImage(path +'marker.png',
      // This marker is 20 pixels wide by 32 pixels tall.
      new google.maps.Size(32, 36),
      // The origin for this image is 0,0.
      new google.maps.Point(0,0),
      // The anchor for this image is the base of the flagpole at 0,32.
      new google.maps.Point(16, 36));
   
 
   if(showMarker == 1) { 
     
    image = new google.maps.MarkerImage(path +'marker.png',
      new google.maps.Size(32, 36),
      new google.maps.Point(0,0),
      new google.maps.Point(16, 36));
      
    var shadow = new google.maps.MarkerImage(path +'shadow.png',
      new google.maps.Size(60, 36),
      new google.maps.Point(0,0),
      new google.maps.Point(16, 36));   
    
    marker = new google.maps.Marker({
    position: mlatlng, 
    map: map,
    icon: image,
    shadow: shadow,
    animation: google.maps.Animation.DROP,
    title:title
   });
  
	/* Not used for now
	var infowindow = new google.maps.InfoWindow({
    content: info
});
  google.maps.event.addListener(marker, 'click', function() {
  infowindow.open(map,marker);
});
*/

	if (admin && (op == "edit" || op == "block-edit")) {
	
	google.maps.event.addListener(map, "dragstart", function() {
	});

	google.maps.event.addListener(map, "dragend", function() {
       
		latlng = map.getCenter();
		
		$('#edit-content-gmap-lat').val(latlng.lat());
		$('#edit-content-gmap-lng').val(latlng.lng());
		});
	
	
	marker.setDraggable(true);
	google.maps.event.addListener(marker, "dragstart", function() {});

	google.maps.event.addListener(marker, "dragend", function() {
       
		latlng = marker.getPosition();
		
		$('#edit-content-gmap-mlat').val(latlng.lat());
		$('#edit-content-gmap-mlng').val(latlng.lng());
		
      });
      
      google.maps.event.addListener(map, "zoom_changed", function() {
		$('#edit-content-gmap-zoom').val(map.getZoom());
		});

 }
     }
        
});

})(jQuery);