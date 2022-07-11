package com.fyp.remoteLab.controller;

import com.fyp.remoteLab.model.Input;
import com.fyp.remoteLab.service.Service;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin(maxAge = 3600)
@RequestMapping("/input")
public class InputController {
    @Autowired
    private Service service;
    @PostMapping("/add")
    public ResponseEntity addData(@RequestBody Input input){
        return service.saveInputs(input);
    }
    @GetMapping("/get")
    public ResponseEntity<Input> fetchData(){
        return  service.getData();
    }
}
