<?php
/**
 * @file
 * drupalcamp_migrate.events.inc
 */

class MigrateContentEventsMigration extends Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);


    $this->description = 'Migrate drupalcamp demo users from json to drupal';
    // Document the source fields
    $fields = array(
      'uuid' => 'Unique ID for each source data row',
      'event_name' => 'Event Name',
      'event_type' => 'Event Type',
      'cost' => 'Event Cost',
      'cost_details' => 'Event Cost Details',
      'phone' => 'Event Phone',
      'email' => 'Event Email',
      'url' => 'Event Website Url',
      'description' => 'Event Description',
      'uid' => 'User who owns this event',
      'organizationId' => 'og_group_ref',
    );

    $json_file = dirname(__FILE__) . '/resources/events.json';
    $this->source = new MigrateSourceList(new DrupalCampEventListJSON($json_file), new DrupalCampEventItemJSON($json_file, array()), $fields);

    $this->destination = new MigrateDestinationNode('event');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array('type' => 'varchar',
          'length' => '255',
          'not null' => TRUE,
          'description' => 'Node ID'),
      ),
      MigrateDestinationNode::getKeySchema()
    );


    $this->addFieldMapping('title', 'event_name');
    $this->addFieldMapping('field_event_type', 'event_type');
    $this->addFieldMapping('field_event_cost', 'cost');
    $this->addFieldMapping('field_event_cost_details', 'cost_details');
    $this->addFieldMapping('field_event_description', 'description');
    $this->addFieldMapping('field_event_phone', 'phone');
    $this->addFieldMapping('field_event_email', 'email');
    $this->addFieldMapping('field_event_url', 'url');
    $this->addFieldMapping('uid', 'uid');

    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('status')->defaultValue('1');
  }

  /**
   * Complete function
   * Added translation and update og_group_ref
   *
   * @param $entity
   * @param stdClass $row
   */
  public function complete($entity, stdClass $row) {

    $handler = entity_translation_get_handler('node', $entity);

    $translation = array(
      'translate' => 0,
      'status' => 1,
      'language' => 'fr',
      'source' => 'en',
    );

    $values = array();

    $entity->title_field['fr'][0]['value'] = $row->event_name_fr;
    $values['title_field']['fr'][0]['value'] = $row->event_name_fr;

    if (isset($row->cost_details_fr)) {
      $entity->field_event_cost_details['fr'][0]['value'] = $row->cost_details_fr;
      $values['field_event_cost_details']['fr'][0]['value'] = $row->cost_details_fr;
    }

    $entity->field_event_description['fr'][0]['value'] = $row->description_fr;
    $values['field_event_description']['fr'][0]['value'] = $row->description_fr;

    $handler->setTranslation($translation, $values);
    $handler->saveTranslations();

    node_save($entity);


    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'organizations')
      ->propertyCondition('status', 1) /* Status to make sure it is published */
      ->propertyCondition('uuid', $row->organizationId)
      ->range(0, 1);
    $result = $query->execute();

    $org_ref = array_keys($result['node']);
    $parent_ref = $org_ref[0];

    og_group('node', $parent_ref, array('entity_type' => 'node', 'entity' => $entity->nid));

  }
}

class DrupalCampEventItemJSON extends MigrateItemJSON {
  protected $data = array();

  public function getItem($id) {
    $obj = parent::getItem($id);
    $item = $obj->$id;

    $obj = $item;

    //don't need user info
    unset($obj->contact);

    //get uid
    $uid = entity_uuid_load('user', array($id));
    $obj->uid = array_keys($uid);
    $obj->uid = $obj->uid[0];

    $obj->phone = $obj->event_info->phone;
    if ($obj->event_info->phone_ext != '') {
      $obj->phone .= 'x' . $obj->event_info->phone_ext;
    }

    $obj->email = $obj->event_info->email;
    $obj->url = $obj->event_info->url;

    unset($obj->event_info);

    $obj->organizationId = $obj->organization->organizationId;
    $obj->desc = $obj->description;

    $obj->event_name_fr = $obj->event_name->fr;
    $obj->event_name = $obj->event_name->en;

    if (isset($obj->cost_details->fr)) {
      $obj->cost_details_fr = $obj->cost_details->fr;
      $obj->cost_details = $obj->cost_details->en;
    }

    $obj->description_fr = $obj->description->fr;
    $obj->description = $obj->description->en;
    unset($obj->organization);

    return $obj;
  }
}

class DrupalCampEventListJSON extends MigrateListJSON {

  protected function getIDsFromJSON(array $data) {
    return array_keys($data);
  }
}
