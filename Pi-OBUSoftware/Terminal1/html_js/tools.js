function getCurrentPointOfView() {
    return map.getBounds().getCenter().toUrlValue(6);
}

function appendMarker(jsonObj)
{
    var marker = new google.maps.Marker({
        position: new google.maps.LatLng( jsonObj.geometry.location.lat, jsonObj.geometry.location.lng ),
        map: map,
        title: jsonObj.name,
        animation: google.maps.Animation.DROP,
        icon: jsonObj.icon
    });

    google.maps.event.addListener(marker, 'click', function() {
        QtPlaces.markerClicked( jsonObj['reference'] );
    });
    markers.push(marker)
}

function gotoPlace(json, zoom)
{
    map.setCenter( new google.maps.LatLng( json.geometry.location.lat, json.geometry.location.lng ) );
    map.setZoom(zoom);
}

function gotoLocation( lat, lng, zoom )
{
    map.setCenter( new google.maps.LatLng( lat, lng ) )
    map.setZoom(zoom)
}

function recreateSearchCircle(lat, lng, radius)
{
    var searchCircleOptions = {
      strokeColor: "#000000",
      strokeOpacity: 0.75,
      strokeWeight: 1,
      fillColor: "#000000",
      fillOpacity: 0.35,
      map: map,
      center: new google.maps.LatLng( lat, lng ),
      radius: radius
    };
    searchCircle = new google.maps.Circle(searchCircleOptions);
}

function zoom(x)
{
    map.setZoom(x);
}

function addMarker(mac, lat, lng, temp, hum, mac_head)
{
    var infowindow = new google.maps.InfoWindow({
          content:" "
          });
    if (mac<10) mac="0"+mac;
    if (mac_head<10) mac_head="0"+mac_head;
    var marker = new google.maps.Marker({
        position: new google.maps.LatLng( lat, lng),
        map: map,
        optimized: false
      });
    marker.addListener('click', function() {
        map.setZoom(18);
        map.setCenter(marker.getPosition());
      });
    //style="visibility: hidden;"
   // alert("TEST");
    if(mac == mac_head){
        google.maps.event.addListener(marker, 'rightclick', function() {
                infowindow.setContent('<div style="width:100%;height:100%;overflow:hidden">' +
                     '<p>Sensor '+ mac +'</p>' +
                     '<p>Nhiet Do: '+ temp +'</p>' +
                     '<p>Do Am: '+ hum +'</p>' +
                     '<p><button id="getTemp" onclick="GetTempHump('+mac+')">Get Temp & Hump</button></p>'+
                     '<p><button id="takePhoto" onclick="TakePhoto('+mac+')">Take Photo</button></p>'+
                     '<p><button id="showbtn" onclick="ShowImage()">Show/Hide Image</button></p>'+
                     '<p><img id="test" height="100" src = "http://lab411s.esy.es/sg/camerasensor_'+mac+'.jpg" /></p> '+
                     '</div>'
                     );
              infowindow.open(map,marker);
              });
    } else {
        google.maps.event.addListener(marker, 'rightclick', function() {
                infowindow.setContent('<div style="width:100%;height:100%;overflow:hidden">' +
                     '<p>Sensor '+ mac +'</p>' +
                     '<p>Cluster Head: '+ mac_head +'</p>' +
                     '<p>Nhiet Do: '+ temp +'</p>' +
                     '<p>Do Am: '+ hum +'</p>' +
                     '<p><button id="getTemp" onclick="GetTempHump('+mac+')">Get Temp & Hump</button></p>'+
                     '<p><button id="takePhoto" onclick="TakePhoto('+mac+')">Take Photo</button></p>'+
                     '<p><button id="showbtn" onclick="ShowImage()">Show/Hide Image</button></p>'+
                     '<p><img id="test" height="100" src = "http://lab411s.esy.es/sg/camerasensor_'+mac+'.jpg" /></p> '+
                     '</div>'
                     );
              infowindow.open(map,marker);
              });
    }

    markers.push(marker);
}

//'<p><table id="imgTable">'+
//'<tr> <td>Sensor 01</td> <td>Sensor 02</td> <td>Sensor 03</td> </tr>'+
//'<tr> <td>Time 01</td> <td>Time 02</td> <td>Time 03</td> </tr>'+
//'<tr> <td> <img height="100" src="http://lab411s.esy.es/sg/camerasensor_08.jpg"/>  </td> '+
//'<td> <img height="100" src="http://lab411s.esy.es/sg/camerasensor_08.jpg"/> </td>'+
//'<td> <img height="100" src="http://lab411s.esy.es/sg/camerasensor_09.jpg"/> </td> </tr>'+
//+'</table></p>'+

document.getElementById("files").onchange = function () {
    var reader = new FileReader();

    reader.onload = function (e) {
        // get loaded data and render thumbnail.
        document.getElementById("image").src = e.target.result;
        window.alert("aaaa");
    };
    window.alert("aaaa");
    // read the image file as a data URL.
    reader.readAsDataURL(this.files[0]);
};

function GetTempHump(mac){
    //alert("oko");
    myObject.mySendCommand(mac,0);
    //JSConsole.inset
    //JSconsole.insertPlainText("a;sdlkfjalskdjweor");
    //Qt.sendCommand(33,0);
    //alert("oko");
}

function TakePhoto(mac){
    myObject.mySendCommand(mac,1);
}

function ShowImage() {
    var img = document.getElementById('test');
    //img.style.visibility = 'visible';
    //alert("oko");
//    jsConsole.insertPlainText("a;sdlkfjalskdjweor");
//    Qt.sendCommand(33,0);
    //jsConsole.printData("qwerasdfzxcv");
  // myObject.mySendCommand(8,0);
    var btn = document.getElementById('showbtn');
    if (img.style.visibility=='hidden') {
        img.style.visibility='visible';
        img.height=100;
       // img.style.width=100;
    }else{
        img.style.visibility='hidden';
        img.height=0;
        //img.style.width=0;
    }
    //btn.value="Hide Image";
}

function HideImage() {
    var img = document.getElementById('test');
    img.style.visibility = 'hidden';
}

function addMyMarker(lat, lng)
{
    MyMarker = new google.maps.Marker({
        position: new google.maps.LatLng(lat, lng),
        map: map,
        icon: 'http://maps.google.com/mapfiles/ms/icons/blue-dot.png',
        optimized: false
    });
    MyMarker.addListener('click', function() {
        map.setZoom(18);
        map.setCenter(MyMarker.getPosition());
      });
}

function addTrackingMarker(mac, lat, lng, temp, hum, mac_head, t1hour, t1min, t1sec, t2hour, t2min, t2sec, t3hour, t3min, t3sec){
    if(t1hour<10) t1hour = "0" + t1hour;
    if(t1min<10) t1min = "0" + t1min;
    if(t1sec<10) t1sec = "0" + t1sec;
    if(t2hour<10) t2hour = "0" + t2hour;
    if(t2min<10) t2min = "0" + t2min;
    if(t2sec<10) t2sec = "0" + t2sec;
    if(t3hour<10) t3hour = "0" + t3hour;
    if(t3min<10) t3min = "0" + t3min;
    if(t3sec<10) t3sec = "0" + t3sec;

    var infowindow = new google.maps.InfoWindow({
          content:" "
          });
    if (mac<10) mac="0"+mac;
    var marker = new google.maps.Marker({
        position: new google.maps.LatLng( lat, lng),
        label: mac,
        map: map,
        optimized: false
      });
    marker.addListener('click', function() {
        map.setZoom(18);
        map.setCenter(marker.getPosition());
      });
    //style="visibility: hidden;"
    google.maps.event.addListener(marker, 'rightclick', function() {
            infowindow.setContent('<div style="width:100%;height:100%;overflow:hidden">' +
                 '<p>Sensor '+ mac +'</p>' + '<p>Nhiet Do: '+ temp +'</p>' +
                 '<p>Do Am: '+ hum +'</p>' +
                 '<p><button id="getTemp" onclick="GetTempHump('+mac+')">Get Temp & Hump</button></p>'+
                 '<p><button id="takePhoto" onclick="TakePhoto('+mac+')">Take Photo</button></p>'+
                 '<p><button id="showbtn" onclick="ShowImage()">Show/Hide Image</button></p>'+
                 '<p><img id="test" height="100" src = "http://lab411s.esy.es/sg/camerasensor_'+mac+'.jpg" /></p> '+
                 '<p><button  id="showTracking" style="disabled:true" onclick="ShowTrackingImage()">Show Tracking Object</button>  </p>'+
                 '<p><table id="imgTable" align="center" border="1px" style="visibility:hidden" >' +
                 '<tr> <th>Sensor 05</th> <th>Sensor 08</th> <th>Sensor 09</th> </tr>'+
                 '<tr> <td>'+t1hour+':'+t1min+':'+t1sec+'</td> <td>'+t2hour+': '+t2min+':'+t2sec+'</td> <td>'+t3hour+':'+t3min+':'+t3sec+'</td> </tr>'+
                 '<tr> <td> <img height="100" src="http://lab411s.esy.es/sg/camerasensor_05.jpg"/>  </td> '+
                 '<td> <img height="100" src="http://lab411s.esy.es/sg/camerasensor_08.jpg"/> </td>'+
                 '<td> <img height="100" src="http://lab411s.esy.es/sg/camerasensor_09.jpg"/> </td> </tr>'+
                 '</table></p>'+
                 '</div>'
                 );
          infowindow.open(map,marker);
          });
    markers.push(marker);
}

function ShowTrackingImage(){
    var table = document.getElementById('imgTable');
    //img.style.visibility = 'visible';
    if (table.style.visibility=='hidden') {
        table.style.visibility='visible';
    }else{
        table.style.visibility='hidden';
    }
}

function addDirectionArrow(lat1, lng1, lat2, lng2){
    var lineSymbol = {
              path: google.maps.SymbolPath.FORWARD_CLOSED_ARROW
            };
    var arrow = new google.maps.Polyline({
              path: [{lat: lat1, lng: lng1}, {lat: lat2, lng: lng2}],
              icons: [{
                icon: lineSymbol,
                strokeOpacity: 1.0,
                strokeWeight: 2,
                //offset: '100%'
              }],
                strokeColor: "red",
              //map: map
            });
    arrow.setMap(map);
    dirArrows.push(arrow);
//    arrows.push(arrow);
}

function addTempVector(lat1, lng1, lat2, lng2){
    var lineSymbol = {
              path: google.maps.SymbolPath.FORWARD_CLOSED_ARROW
            };
    var arrow = new google.maps.Polyline({
              path: [{lat: lat1, lng: lng1}, {lat: lat2, lng: lng2}],
              icons: [{
                icon: lineSymbol,
                strokeOpacity: 1.0,
                strokeWeight: 2,
                //offset: '100%'
              }],
              //map: map
            });
    arrow.setMap(map);
    arrows.push(arrow);
}

function addNewTempVector(index, lat1, lng1, lat2 ,lng2){
    var lineSymbol = {
              path: google.maps.SymbolPath.FORWARD_CLOSED_ARROW
            };
    var arrow = new google.maps.Polyline({
              path: [{lat: lat1, lng: lng1}, {lat: lat2, lng: lng2}],
              icons: [{
                icon: lineSymbol,
                strokeOpacity: 1.0,
                strokeWeight: 2,
                //offset: '100%'
              }],
              //map: map
            });
    arrow.setMap(map);
    arrows.splice(index, 0, arrow);
}

function moveMyMarker(lat, lng)
{
    /*
    setTimeout(function() {
        marker.setPosition(new google.maps.LatLng(lat, lng));
        map.panTo(new google.maps.LatLng(lat, lng));
    }, 1500);
    */
    MyMarker.setPosition(new google.maps.LatLng(lat, lng));
    //marker.setPosition(new google.maps.LatLng(lat, lng));
}
function setGreenMarker(i)
{
    markers[i].setIcon('http://maps.google.com/mapfiles/ms/icons/green-dot.png');
}

function setRedMarker(i)
{
    markers[i].setIcon('http://maps.google.com/mapfiles/ms/icons/red-dot.png');
    
}

function setYellowMarker(i){
    markers[i].setIcon('http://maps.google.com/mapfiles/ms/icons/yellow-dot.png');
}

function setPinkMarker(i){
    markers[i].setIcon('http://maps.google.com/mapfiles/ms/icons/pink-dot.png');
}

function setOrangeMarker(i){
    markers[i].setIcon('http://maps.google.com/mapfiles/ms/icons/orange-dot.png');
}

function setRedPin(i){
    var redPinkIcon = {
        url: "http://maps.google.com/mapfiles/kml/pushpin/red-pushpin.png",
        scaledSize: new google.maps.Size(30, 30), // scaled size
        origin: new google.maps.Point(0,0), // origin
        anchor: new google.maps.Point(0, 0) // anchor
    };
    markers[i].setIcon(redPinkIcon);
}

function setGreenPin(i){
    markers[i].setIcon('http://maps.google.com/mapfiles/kml/pushpin/grn-pushpin.png');
}

function clearMarker(i){
    markers[i].setMap(null);
}

function clearArrow(i){
    arrows[i].setMap(null);
}

function removeArrow(i){
    arrow.splice(i,1);
}

function showMarker(i)
{
    markers[i].setMap(map);
}

function setMapOnAll(map) {
  for (var i = 0; i < markers.length; i++) {
    markers[i].setMap(map);
  }
}

function setArrowOnAll(map){
    for(var i=0; i < arrows.length; i++){
        arrows[i].setMap(map);
    }
}

function showAllMarkers()
{
    setMapOnAll(map);
    //setArrowOnAll(map);
}

function clearAllMarkers()
{
    setMapOnAll(null);
    //setArrowOnAll(null);
}

function removeAllMarkers()
{
    while(markers.length)
        markers.pop().setMap(null);
}

function removeAllArrows(){
    while(arrows.length)
        arrows.pop().setMap(null);
}

function removeDirArrows()
{
    while(dirArrows.length)
        dirArrows.pop().setMap(null);
}

function initMyLocation(x, y)
{
    MyMarker = new google.maps.Marker({
            position: new google.maps.LatLng( x, y),
            map: map,
            optimized: false
          });
    map.panTo( new google.maps.LatLng( x, y ) );
}

function MyLocation(x, y)
{

}

