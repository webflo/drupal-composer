<?php
/**
 * Created by PhpStorm.
 * User: nealv
 * Date: 17/12/14
 * Time: 15:48
 */

use Behat\Behat\Tester\Exception\PendingException;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalDriverManager;

class CegekaContext implements DrupalSubContextInterface {
  private $drupal;

  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Checks, that form element with specified label is visible on page.
   *
   * @Then /^(?:|I )should see an? "(?P<label>[^"]*)" form element$/
   */
  public function assertFormElementOnPage($label) {
    $element = $this->getSession()->getPage();
    $nodes = $element->findAll('css', '.form-item label');
    foreach ($nodes as $node) {
      if ($node->getText() === $label) {
        if ($node->isVisible()) {
          return;
        }
        else {
          throw new \Exception("Form item with label \"$label\" not visible.");
        }
      }
    }
    throw new ElementNotFoundException($this->getSession(), 'form item', 'label', $label);
  }

  /**
   * Checks, that form element with specified label and type is visible on page.
   *
   * @Then /^(?:|I )should see an? "(?P<label>[^"]*)" (?P<type>[^"]*) form element$/
   */
  public function assertTypedFormElementOnPage($label, $type) {
    $container = $this->getSession()->getPage();
    $pattern = '/(^| )form-type-' . preg_quote($type) . '($| )/';
    $label_nodes = $container->findAll('css', '.form-item label');
    foreach ($label_nodes as $label_node) {
      // Note: getText() will return an empty string when using Selenium2D. This
      // is ok since it will cause a failed step.
      if ($label_node->getText() === $label
        && preg_match($pattern, $label_node->getParent()->getAttribute('class'))
        && $label_node->isVisible()
      ) {
        return;
      }
    }
    throw new ElementNotFoundException($this->getSession(), $type . ' form item', 'label', $label);
  }

  /**
   * Checks, that element with specified CSS is not visible on page.
   *
   * @Then /^(?:|I )should not see an? "(?P<label>[^"]*)" form element$/
   */
  public function assertFormElementNotOnPage($label) {
    $element = $this->getSession()->getPage();
    $nodes = $element->findAll('css', '.form-item label');
    foreach ($nodes as $node) {
      // Note: getText() will return an empty string when using Selenium2D. This
      // is ok since it will cause a failed step.
      if ($node->getText() === $label && $node->isVisible()) {
        throw new \Exception();
      }
    }
  }

  /**
   * Checks, that form element with specified label and type is not visible on page.
   *
   * @Then /^(?:|I )should not see an? "(?P<label>[^"]*)" (?P<type>[^"]*) form element$/
   */
  public function assertTypedFormElementNotOnPage($label, $type) {
    $container = $this->getSession()->getPage();
    $pattern = '/(^| )form-type-' . preg_quote($type) . '($| )/';
    $label_nodes = $container->findAll('css', '.form-item label');
    foreach ($label_nodes as $label_node) {
      // Note: getText() will return an empty string when using Selenium2D. This
      // is ok since it will cause a failed step.
      if ($label_node->getText() === $label
        && preg_match($pattern, $label_node->getParent()->getAttribute('class'))
        && $label_node->isVisible()
      ) {
        throw new ElementNotFoundException($this->getSession(), $type . ' form item', 'label', $label);
      }
    }
  }
}
