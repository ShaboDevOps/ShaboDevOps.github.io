package com.fyp.remoteLab.repo;

import com.fyp.remoteLab.model.Result;
import org.springframework.data.jpa.repository.JpaRepository;

public interface ResultRepo extends JpaRepository<Result, Long> {
}
