var map;
var markers= [];
var arrows= [];
var QtPlaces;
var MyMarker;

var searchCircle;

function initialize(x, y, z)
{
    var myOptions = {
        center: new google.maps.LatLng(x, y),
        zoom: z,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        panControl: true
    };
    map = new google.maps.Map(document.getElementById("map_canvas"), myOptions)
}
