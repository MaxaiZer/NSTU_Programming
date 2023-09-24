using System.ComponentModel.DataAnnotations;

public class Student
{

    [Required]
    [RegularExpression(@"[a-zA-Z-]+$", ErrorMessage = "Name: only letters are allowed.")]
    [StringLength(50, MinimumLength = 2)]
    public string Name { get; set; }

    [Required]
    [RegularExpression(@"[a-zA-Z-]+$", ErrorMessage = "Surname: only letters are allowed.")]
    [StringLength(50, MinimumLength = 2)]
    public string Surname { get; set; }
}
