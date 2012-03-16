/**
 * @author David Sichau
 */
function Connections(connectionFile) {
	//private stuff
	var connectionFile = connectionFile;
	var connections = {};

	//public stuff
	// parse the input file and prints it to id
	this.filters = [];

	this.loadJSON = function() {
		console.debug("load JSON and parse the JSON");
		$.getJSON(connectionFile, function(json) {
			connections = json;
		});
	};
	//prints the JSON in div with id=id
	this.printJSON = function(id) {
		console.debug("generate html json with input forms");

		var html = "";
		html += '<div id="' + id + '"><button id="exportConnections">Export</button><button id="addConnection">Add new Connection</button><button id="delConnection">Remove Connection</button><ul>';

		$.each(connections, function() {
			$.each(this, function(id) {
				html += '<li id="' + id + '"><ul  type="none">';
				$.each(this, function(index, value) {
					if($.isArray(value)) {
						html += '<li>' + index + ': <ul>';
						$.each(this, function(id2) {
							html+="<li>";
							$.each(this, function(index2, value2) {
								
									html += index2 + ': ' + value2 + "<br />";
							});
							html+="</li>";
						});
						html += '</ul></li>'
					} else {
						html += '<li>' + index + ": " + value + '</li>';
					}
				});
				html += '</ul></li>';
			});
		});
		html += '</ul></div>';
		return html;
	};
	// generate a txt output of JSON to copy in your config file
	this.generateJSONtxt = function(id) {
		console.debug("generate text json");
		var html = "";
		$.each(connections, function(root) {
			html += '<div id="' + id + '"> {<br />"' + root + '": [ <ul type="none">';
			$.each(this, function(id) {
				html += '{';
				$.each(this, function(index, value) {
					if($.isArray(value)) {
						//if no parameters are given
						if(value.length == 0) {
							html += '<li>"' + index + '":[ ],</li>';
						} else {
							html += '<li>"' + index + '":[ <ul type="none">';
							$.each(this, function(id2) {
								html += '<li>{<ul type="none">';
								$.each(this, function(index2, value2) {
									if(index2 == 'param') {
										html += ' <li>"' + index2 + '": "' + value2 + '"</li>';
									} else {
										html += '<li>"' + index2 + '": "' + value2 + '",</li>';
									}
								});
								html = html.substring(0, html.length - 6);
								html += '</li></ul>}</li>,';
							});
							html = html.substring(0, html.length - 1);
							html += '</ul>],</li>'
						}
					} else {
						html += '<li>"' + index + '": "' + value + '",</li>';
					}
				});
				html = html.substring(0, html.length - 6);
				html += '},';
			});
			html = html.substring(0, html.length - 1);
			html += '</ul>] <br /> }</div>';
		});
		return html;
	}

	this.getJSON = function() {
		return connections;
	}
	
	this.addConnection = function(filterName_, filterIdentifier_, precursors_, ports_){
		console.log(precursors_);
		$.each(connections, function(root, val) {
			connections[root][val.length] = {
				filterName : filterName_,
				identifier : filterIdentifier_,
				precursors : precursors_,
				ports : ports_
			};
		});
		console.log(connections);
		
	}

	this.delConnection = function(filterID) {
		$.each(connections, function(root, value) {
			value = jQuery.grep(value, function(temp, temp2) {
				return temp2 != filterID;
			});
			connections[root] = value;
			console.debug("Parameter deleted");
		});
	}
	// open dialog with the new connection file
	//$(document).on("click",$('#showConnections #export'), function() {
	$('#exportConnections').live("click", function() {
		$("#export_layer").remove();
		var html = completeFilter.connections.generateJSONtxt("export_layer");
		$(html).appendTo('body');
		$(function() {
			$("#export_layer").dialog({
				width : 500
			});
		});
	});
}