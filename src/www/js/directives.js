'use strict';

/* Directives */
var app = angular.module('myApp.directives', ['ngAnimate']);

app.directive('header', function(){

    return {
        restrict: 'AE',
        templateUrl: 'template/header.html'
    }


});


app.directive('top', function(){
    return {
        restrict: 'AE',
        templateUrl: 'template/top.html'
    }
})


app.directive('navigation', function(){
    return {
        restrict: 'AE',
        templateUrl: 'template/nav.html'
    }
})


