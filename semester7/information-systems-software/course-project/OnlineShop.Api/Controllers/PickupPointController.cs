using Microsoft.AspNetCore.Mvc;
using OnlineShop.Api.Entities;
using OnlineShop.Api.Repositories.Contracts;

namespace OnlineShop.Api.Controllers;

[ApiController]
[Route("api/[controller]")]
public class PickupPointController : ControllerBase
{
    private IPickupPointRepository _repository;

    public PickupPointController(IPickupPointRepository repository)
    {
        _repository = repository;
    }

    [HttpGet]
    public ActionResult<IEnumerable<Smartphone>> Get()
    {
        return new JsonResult(_repository.GetAll());
    }

}
