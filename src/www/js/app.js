'use strict';


// Declare app level module which depends on filters, and services
/*angular.module('myApp', [
  'ngRoute',
  'ngAnimate',
  'DWand.nw-fileDialog',
  'myApp.filters',
  'myApp.services',
  'myApp.directives',
  'myApp.controllers',
]).
config(['$routeProvider', function($routeProvider) {
  $routeProvider.when('/', {templateUrl: 'partials/menu.html', controller: 'menu'});
  $routeProvider.when('/grille', {templateUrl: 'partials/grille.html', controller: 'grille'});
  $routeProvider.otherwise({redirectTo: '/'});
}]);*/


var app = angular.module('myApp', [
  'ngMaterial',
  'ngRoute',
  'DWand.nw-fileDialog',
  'myApp.filters',
  'myApp.services',
  'myApp.directives',
  'myApp.controllers',
  'myApp.directives'
  ]);

app.config(['$routeProvider','$locationProvider','$httpProvider', function($routeProvider,$locationProvider,$httpProvider) {
  $routeProvider.when('/', {templateUrl: 'partials/accueil.html', controller: 'menu'});
  $routeProvider.when('/grille', {templateUrl: 'partials/jeu.html', controller: 'grille'});
  $routeProvider.when('/grille/:mode', {templateUrl: 'partials/jeu.html', controller: 'grille'});
}]);