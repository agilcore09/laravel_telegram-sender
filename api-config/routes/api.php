<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\SenderController;

Route::get('/sender', [SenderController::class, 'sender']);
