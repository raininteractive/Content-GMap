<?php
/**
 * @file
 * Administration page callbacks for the content_gmap module.
 */

/**
 * Callback for admin settings page
 */
function content_gmap_admin_settings_form($form_state) {

  $options = node_type_get_names();
  content_gmap_build(0, 'block-edit');

/* Content GMap Content Selection */
  $form['config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node Selection'),
    '#collapsible' => TRUE,
    '#prefix' => t('<p>Content GMap attaches a GMAP to selected nodes</p>')
  );

  $form['config']['content_gmap_node_types'] = array(
  '#type' => 'checkboxes',
  '#title' => t('Add Rain Map Features to these content types'),
  '#options' => $options,
  '#default_value' => variable_get('content_gmap_node_types', array()),
  '#description' => t('Rain Map Fields will be added to these Content Types'),
  );

/* Default Settings */
  $form['info'] = array(
  '#type' => 'fieldset',
  '#title' => t('Default Map Information'),
  '#collapsible' => FALSE,
  '#description' => t('Default Settings for new maps'),
    );

/* Default Map Type */
  $form['info']['content_gmap_type'] = array(
  '#type' => 'select',
  '#title' => t('Map type'),
  '#default_value' => variable_get('content_gmap_type', 'ROADMAP'),
  '#description' => NULL,
  '#options' => array(
  'ROADMAP' => 'the default view',
  'SATELLITE' => 'showing Google Earth satellite images',
  'HYBRID_MAP' => 'showing a mixture of normal and satellite views',
  'TERRAIN' => 'showing a mixture of normal and satellite views'),
  );


  /* Default Zoom Level */

  // Generate Zoom Level Options
  $zoom_levels = array('0' => t('0 - minimum zoom level, whole world'));
  for ($i = 1; $i < 20; $i++) {
    $zoom_levels["$i"] = "$i";
  }

  // Append text to Maximum Level
  $zoom_levels['18'] = t('18 - Street Zoom level');
  $zoom_levels['20'] = t('20 - maximum zoom level');

  $form['info']['content_gmap_zoom'] = array('#type' => 'select',
  '#title' => t('Map zoom level'),
  '#default_value' => variable_get('content_gmap_zoom', '16'),
  '#description' => NULL,
  '#options' => $zoom_levels,
  );

  /* Map Width */
  $form['info']['content_gmap_width'] = array('#type' => 'textfield',
  '#title' => t('Map Width'),
  '#default_value' => variable_get('content_gmap_width', '500'),
  '#field_suffix' => 'px',
  '#description' => NULL,
  '#size' => 10,
  );

  /* Map Height */
  $form['info']['content_gmap_height'] = array('#type' => 'textfield',
  '#title' => t('Map Height'),
  '#default_value' => variable_get('content_gmap_height', '500'),
  '#field_suffix' => 'px',
  '#description' => NULL,
  '#size' => 10,
  );

  /* Deposit Map */
  $form['info']['content_gmap_gmap'] = array(

  '#markup' => '<div id="content-gmap" style="width:600px;height:340px;"></div>',

  );

  /* Field Set for Coordinates	*/
  $form['info']['latlng'] = array(
    '#type' => 'fieldset',
    '#title' => t('Map coordinates'),
    '#collapsible' => FALSE,
    '#description' => t('Geographical coordinates for your location. You can find these if you google - google map latitude longitude as there are webpages that will find the values for you'));

  /* The Map Latitude */
  $form['info']['latlng']['content_gmap_lat'] = array(
    '#type' => 'textfield',
    '#title' => t('Latitude'),
    '#default_value' => variable_get('content_gmap_lat', '35.670363'),
    );

  /* The Map Longitude */
  $form['info']['latlng']['content_gmap_lng'] = array(
    '#type' => 'textfield',
    '#title' => t('Longitude'),
    '#default_value' => variable_get('content_gmap_lng', '139.72653'),
    );

  /* Field Set for Marker Coordinates	*/
  $form['info']['mlatlng'] = array(
  '#type' => 'fieldset',
  '#title' => t('Marker coordinates'),
  '#collapsible' => FALSE,
  '#description' => t('Geographical coordinates for your Marker. This can be the same as the Map coordinates, but if you wish to place the marker at a different location you can specific the coordinates here.'));

  /* Hide Marker */
  $form['info']['mlatlng']['content_gmap_marker'] = array(
  '#type' => 'checkbox',
  '#title' => t('Show Marker'),
  '#default_value' => variable_get('content_gmap_marker', TRUE),
  '#description' => t("If you don't wish to display a marker you can turn if off here. Default is On"),
  );

/* Create some defaults for the Marker Latitudes
 * This is a bracing for the validation
 */

  $mlat_default = variable_get('content_gmap_lat', '35.670363');
  $mlng_default = variable_get('content_gmap_lng', '139.72653');

  /* The Marker Latitude */
  $form['info']['mlatlng']['content_gmap_mlat'] = array(
    '#type' => 'textfield',
    '#title' => t('Latitude'),
    '#default_value' => variable_get('content_gmap_mlat', $mlat_default),
    );

  /* The Marker Longitude */
  $form['info']['mlatlng']['content_gmap_mlng'] = array(
    '#type' => 'textfield',
    '#title' => t('Longitude'),
    '#default_value' => variable_get('content_gmap_mlng', $mlng_default),
    );

  /* Can't get validation function to be called so have to do it here */

  if ($form['info']['mlatlng']['content_gmap_mlng']['#default_value'] == '') {
  $form['info']['mlatlng']['content_gmap_mlng']['#default_value'] = $mlng_default;
    }

  if ( $form['info']['mlatlng']['content_gmap_mlat']['#default_value'] == '') {
  $form['info']['mlatlng']['content_gmap_mlat']['#default_value'] = $mlat_default;
    }

  return system_settings_form($form);
}