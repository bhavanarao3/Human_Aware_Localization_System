add_test( DetectorTest.DetectTest /home/bhavana/midterm/Human_Aware_Localization_System/build/test/cpp-test [==[--gtest_filter=DetectorTest.DetectTest]==] --gtest_also_run_disabled_tests)
set_tests_properties( DetectorTest.DetectTest PROPERTIES WORKING_DIRECTORY /home/bhavana/midterm/Human_Aware_Localization_System/build/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( DetectorTest.PreProcessTest /home/bhavana/midterm/Human_Aware_Localization_System/build/test/cpp-test [==[--gtest_filter=DetectorTest.PreProcessTest]==] --gtest_also_run_disabled_tests)
set_tests_properties( DetectorTest.PreProcessTest PROPERTIES WORKING_DIRECTORY /home/bhavana/midterm/Human_Aware_Localization_System/build/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( DetectorTest.PostProcessTest /home/bhavana/midterm/Human_Aware_Localization_System/build/test/cpp-test [==[--gtest_filter=DetectorTest.PostProcessTest]==] --gtest_also_run_disabled_tests)
set_tests_properties( DetectorTest.PostProcessTest PROPERTIES WORKING_DIRECTORY /home/bhavana/midterm/Human_Aware_Localization_System/build/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( DetectorTest.DrawLabelTest /home/bhavana/midterm/Human_Aware_Localization_System/build/test/cpp-test [==[--gtest_filter=DetectorTest.DrawLabelTest]==] --gtest_also_run_disabled_tests)
set_tests_properties( DetectorTest.DrawLabelTest PROPERTIES WORKING_DIRECTORY /home/bhavana/midterm/Human_Aware_Localization_System/build/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( cpp-test_TESTS DetectorTest.DetectTest DetectorTest.PreProcessTest DetectorTest.PostProcessTest DetectorTest.DrawLabelTest)
